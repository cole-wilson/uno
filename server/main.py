import random
import socketserver
import socket
import markdown2
import sys
import datetime
from flask import Flask
from threading import Thread

# create Flask webserver instance for uno.cole.ws website
webserver = Flask(__name__)

# read and parse markdown readme file and format into index.html
try:
    markdown = open("./README.md").read()
except FileNotFoundError:
    markdown = open("../README.md").read()
index_html = open("./index.html").read().replace("{{MARKDOWN}}", markdown2.markdown(markdown))
deploy_time = datetime.datetime.now()
index_html = index_html.replace("TIME", f"last deploy at: {deploy_time.isoformat()}, # games: ACTIVE_GAMES")

# webserver dynamic entrypoint
hits = 0
@webserver.route("/")
def info_page():
    global hits # use variable globally
    hits += 1
    # add values to page
    return index_html.replace("ACTIVE_GAMES", str(len(games.keys())) + ", uptime: " + str(datetime.datetime.now() - deploy_time) + ", pageviews: " + str(hits))


# stores all current games
games = {}

# for backwards compatibility on 3.8
if "timeout" in dir(socket):
    TimeoutError = socket.timeout


# basic class (essentially just struct) to store Game data
class Game:
    def __init__(self, code, server_sock):
        self.clients = [server_sock]
        self.code = code
        self.players = 1
        self.started = False

# custom handler for socket requests
class UnoTCPHandler(socketserver.BaseRequestHandler):
    # all print statements just for debugging!
    def handle(self):
        print("new connection\n\n")
        player_index = None

        initial_data = self.request.recv(1024).strip().strip(b"\x00").decode()
        print(">>>", initial_data)
        join_code = None

        # client is trying to host a new game:
        if initial_data == "new":
            # generate random code and hope for no collisions!
            join_code = "".join(random.choices("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890", k=6))
            # join_code = "DEBUG"

            # send code back to server
            print("code is", join_code)
            self.request.sendall(join_code.encode())

            # add game into entry of all games (in the dictionary)
            games[join_code] = Game(join_code, self.request)
            player_index = 0 # host is always index 0

            # wait for host to start the game
            data = self.request.recv(1024)
            if data == b"start":
                games[join_code].started = True
                for client in games[join_code].clients:
                    # send the # of players to each other client including the host
                    client.sendall(str(len(games[join_code].clients)).encode())

        else: # the client is joining a game
            if initial_data in games:
                join_code = initial_data
                player_index = games[join_code].players
                # set to next player index
                games[join_code].players += 1

                # add socket connection to list of all clients
                games[join_code].clients.append(self.request)

                # send the new player id back to the client
                self.request.sendall(f"{player_index}".encode())
            else: # game doesn't exist
                self.request.sendall(b"-1")
        
        # from here on out, make sockets non-blocking
        self.request.settimeout(0.1)

        while True:
            try:
                # if data is recieved from client:
                data = self.request.recv(1024)
                print(">>", data)
                if data == b"":
                    # end of connection...
                    return
                # ...echo that data to each otehr client
                for client in games[join_code].clients:
                    if client != self.request: # don't send back to self
                        client.sendall(data)
            except TimeoutError:
                # no data yet...
                pass


# base code from https://docs.python.org/3/library/socketserver.html
if __name__ == "__main__":
    # bind to all adrresses on 8080
    webthread = Thread(target=webserver.run, kwargs={"host":"0.0.0.0", "port":8080})
    # start other thread for webserver
    webthread.start()

    # bind socket program to all addresses on 9999
    HOST, PORT = "", 9999
    ReuseServer = socketserver.ThreadingTCPServer # allow threading for each new connection
    ReuseServer.allow_reuse_address = True # allow reuse
    ReuseServer.allow_reuse_port = True # ""
    with ReuseServer((HOST, PORT), UnoTCPHandler) as server:
        server.serve_forever()
    webthread.join() # join back webserver when done
