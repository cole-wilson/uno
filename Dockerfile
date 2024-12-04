FROM python:3.13.0-alpine

RUN apk update && apk upgrade && \
    apk add --no-cache make g++ bash git openssh curl
RUN apk update \
    && apk add --virtual build-deps gcc python3-dev musl-dev \
    && apk del build-deps

RUN mkdir -p /usr/src/app
WORKDIR /usr/src/app
RUN python -m pip install -U --force-reinstall pip
RUN pip install --no-cache-dir flask markdown2 --break-system-packages

COPY ./server /usr/src/app
COPY ./README.md /usr/src/app

EXPOSE 9999
EXPOSE 8080

CMD ["python", "empty.py"]
# CMD ["read"]
