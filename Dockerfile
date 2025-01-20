FROM alpine:latest AS build
RUN apk update && \
    apk add --no-cache \
        gcc musl-dev make ncurses-dev
ADD . /app
WORKDIR /app
RUN make release

FROM alpine:latest
RUN apk update && \
    apk add ncurses ncurses-libs --no-cache
COPY --from=build /app/curr_proj /usr/local/bin/curr_proj
RUN adduser -S tester
USER tester
ENTRYPOINT ["/usr/local/bin/curr_proj"]