// Source:
// https://richiejp.com/zig-vs-c-mini-http-server
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/_endian.h>
#include <sys/_types/_socklen_t.h>
#include <sys/_types/_ssize_t.h>
#include <sys/errno.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

#if defined(__linux__)
#include <sys/sendfile.h>
#endif

#if defined(__APPLE__)
#include <sys/types.h>
#include <sys/uio.h>
#endif

void removeSubstring(char *s, const char *toremove) {
  while ((s = strstr(s, toremove))) {
    memmove(s, s + strlen(toremove), 1 + strlen(s + strlen(toremove)));
  }
}

static void handleConnection(const int sk, const int public_dir) {
  char recv_buf[BUFSIZ];
  char head_buf[BUFSIZ];
  const size_t buf_len = BUFSIZ - 1;
  char path_buf[256];
  char *file_path;
  ssize_t recv;
  ssize_t sent;
  size_t recv_total = 0;
  size_t sent_total = 0;
  int body_fd;

  while (1) {
    recv = read(sk, recv_buf + recv_total, buf_len - recv_total);

    if (recv < 0) {
      perror("[-] read");
      return;
    }

    if (!recv) {
      dprintf(STDERR_FILENO,
              "\n>>> [-] End of data before header was received\n");
      break;
    }

    recv_total += recv;
    recv_buf[recv_total] = 0;

    if (strstr(recv_buf, "\r\n\r\n") || strstr(recv_buf, "\n"))
      break;

    if (recv_total >= buf_len) {
      dprintf(STDERR_FILENO, "[-] Exceeded buffer reading header\n");
      return;
    }
  }

  printf(">>> [+] "
         "Received:\n----------------------------------------------------------"
         "-----------------------\n%s\n----------------------------------------"
         "----------------------------------------\n",
         recv_buf);

  memcpy(path_buf, recv_buf + 4, 20);
  removeSubstring(path_buf, "HTTP/1.1");

  printf(">>> [PATH] %s", path_buf);
 
  if (strcmp("/", path_buf) < 0) {
    strcpy(path_buf, "index.html");
    file_path = path_buf;
  }
  printf(">>> [?] Requested file %s", file_path);


  printf(">>> Route match %i", strcmp("/api", file_path));


  body_fd = openat(public_dir, file_path, O_RDONLY);

  if (body_fd < 0 && errno == ENOENT) {
    strcpy(file_path + strlen(file_path), ".html");
    body_fd = openat(public_dir, file_path, O_RDONLY);
    printf("[-] Failed opening %s", file_path);
  }
  printf("\n");

  if (body_fd < 0) {
    perror("[-] openat");
    return;
  }

  char file_buf[BUFSIZ];
  read(body_fd, file_buf, BUFSIZ);
  printf(">>> %s", file_buf);

   const char* const http_head =
     "HTTP/1.1 200 OK\r\n"
     "Connection: close\r\n"
     "Content-Type %s\r\n"
     "Content-Length %ll\r\n"
     "\r\n";
   const char *mime = "text/html";
   // @TODO mime type matching

   struct stat body_stat;
   if (fstat(body_fd, &body_stat)) {
     perror("[-] fstat");
     close(body_fd);
     return;
   }
   sprintf(head_buf, http_head, mime, body_stat.st_size);

   while (sent_total < strlen(http_head)) {
     sent = write(sk, head_buf + sent_total, strlen(head_buf));
     if (sent < 0) {
       perror("[-] write");
       close(body_fd);
       return;
     }

     sent_total += sent;
   }

   do {
     /* sent = sendfile(sk, body_fd, NULL, body_stat.st_size); */
     sent = sendfile(body_fd, sk, 0, &body_stat.st_size, NULL, 0);
     if (sent < 0) {
       perror("[-] sendfile");
     }
     sent_total += sent;
   } while (sent > 0);

  close(body_fd);
  return;
}

int main(int argc, char *argv[]) {
  const pid_t orig_parent = getpid();
  const struct sockaddr_in self_addr = {.sin_family = AF_INET,
                                        .sin_port = htons(1234),
                                        .sin_addr = {htonl(INADDR_LOOPBACK)}};

  const int listen_sk = socket(AF_INET, SOCK_STREAM, 0);
  const int public_dir = open(argv[1], O_RDONLY);
  struct sockaddr client_addr;
  socklen_t addr_len;

  if (argc < 2) {
    dprintf(STDERR_FILENO, "Usage %s <public dir>\n", argv[0]);
    return 1;
  }
  printf("Serving %s\n", argv[1]);

  if (bind(listen_sk, (struct sockaddr *)&self_addr, sizeof(self_addr))) {
    perror("bind");
    return 1;
  }

  if (listen(listen_sk, 8)) {
    perror("listen");
    return 1;
  }

  printf("\n>>> Listening ...");

  while (orig_parent == getpid()) {
    const int sk = accept(listen_sk, &client_addr, &addr_len);

    if (sk < 0) {
      perror("[-] accept");
      break;
    }

    printf("\n>>> [+] Accept Connection\n");

    handleConnection(sk, public_dir);
    close(sk);
  }

  return 0;
}
