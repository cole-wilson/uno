import random
import socketserver
import socket
import markdown2
import sys
import datetime
from flask import Flask
from threading import Thread

webserver = Flask(__name__)

try:
    markdown = open("./README.md").read()
except FileNotFoundError:
    markdown = open("../README.md").read()
index_html = open("./index.html").read().replace("{{MARKDOWN}}", markdown2.markdown(markdown))
deploy_time = datetime.datetime.now()
index_html = index_html.replace("TIME", f"last deploy at: {deploy_time.isoformat()}, # games: ACTIVE_GAMES")

hits = 0

@webserver.route("/")
def info_page():
    global hits
    hits += 1
    return index_html.replace("ACTIVE_GAMES", str(len(games.keys())) + ", uptime: " + str(datetime.datetime.now() - deploy_time) + ", pageviews: " + str(hits))

games = {}


if "timeout" in dir(socket):
    TimeoutError = socket.timeout

class Game:
    def __init__(self, code, server_sock):
        self.clients = [server_sock]
        self.code = code
        self.players = 1
        self.started = False


class UnoTCPHandler(socketserver.BaseRequestHandler):
    def handle(self):
        print("new connection\n\n")
        player_index = None

        initial_data = self.request.recv(1024)
        print(f"got `{initial_data}`")
        initial_data = initial_data.strip().strip(b"\x00").decode()
        print(f"which is `{initial_data}`")
        join_code = None
        if initial_data == "new":
            join_code = "".join(random.choices("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890", k=6))
            # join_code = "DEBUG"
            print("code", join_code)
            self.request.sendall(join_code.encode())
            games[join_code] = Game(join_code, self.request)
            player_index = 0
            data = self.request.recv(1024)
            if data == b"start":
                games[join_code].started = True
                for client in games[join_code].clients:
                    client.sendall(str(len(games[join_code].clients)).encode())

        else:
            # print("new", initial_data)
            if initial_data in games:
                join_code = initial_data
                player_index = games[join_code].players
                games[join_code].players += 1
                games[join_code].clients.append(self.request)
                self.request.sendall(f"{player_index}".encode())
            # elif games[join_code].started:
                # self.request.sendall(b"too late")
            else:
                self.request.sendall(b"-1")

        self.request.settimeout(0.1)

        while True:
            try:
                data = self.request.recv(1024)
                print(">>", data)
                if data == b"":
                    return
                for client in games[join_code].clients:
                    if client != self.request:
                        client.sendall(data)
            except TimeoutError:
                pass

            # self.request.sendall(str(games[join_code].queue.qsize()).encode())

            # if not games[join_code].queue.empty():
                # self.request.sendall(games[join_code].queue.get())

            # self.request.sendall(self.data.upper())


# base code from https://docs.python.org/3/library/socketserver.html
if __name__ == "__main__":
    webthread = Thread(target=webserver.run, kwargs={"host":"0.0.0.0", "port":8080})
    webthread.start()

    HOST, PORT = "", 9999
    ReuseServer = socketserver.ThreadingTCPServer
    ReuseServer.allow_reuse_address = True
    ReuseServer.allow_reuse_port = True
    with ReuseServer((HOST, PORT), UnoTCPHandler) as server:
        server.serve_forever()
    webthread.join()
