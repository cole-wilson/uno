# Dockerfile for Caprover server deploy
FROM python:3.13.0-alpine

# install dependencies
RUN apk update && apk upgrade && \
    apk add --no-cache make g++ bash git openssh curl
RUN apk update \
    && apk add --virtual build-deps gcc python3-dev musl-dev \
    && apk del build-deps

# create the directories and install pip modules
RUN mkdir -p /usr/src/app
WORKDIR /usr/src/app
RUN python -m pip install -U --force-reinstall pip

# Didn't want to deal with Venv in 3.13 so force global install
RUN pip install --no-cache-dir flask markdown2 --break-system-packages

# copy files and readme to working diirectory
COPY ./server /usr/src/app
COPY ./README.md /usr/src/app

# ecpose ports (9999 for SFML socket, 8080 for public site)
EXPOSE 9999
EXPOSE 8080

# entrypoint
CMD ["python", "main.py"]
