#include "SpreadsheetServer.h"



int main()
{
   int socketfd, numBytes;
   char buffer[BUFFER_SIZE];
   struct sockaddr_in serv_addr;
   struct hostent* server;

   socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
   if (socketfd < 0)
      die("Error creating socket");

   server = gethostbyname(LOCAL_HOST);
   if (!server)
      die("Host does not exist");

   memset(&serv_addr, 0, sizeof (serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
   serv_addr.sin_port = htons(PORT_NO);

   if (connect(socketfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
      die("Unable to connect client to server");
   /*FILE* fd = fdopen(socketfd, "r+");
   if (!fd)
      die("Unable to open fd"); */

   while (true)
   {
      memset(buffer, 0, BUFFER_SIZE);
      numBytes = read(socketfd, buffer, BUFFER_SIZE);
      if (numBytes < 0)
         die("Could not read from socket");
      //fflush(fd);
      trimEnd(buffer);
      if (strcmp(buffer, "U got served bitch!") == 0)
      {
         printf("%s\n", buffer);
         break;
      }
      printf("%s", buffer);

      // numBytes = read(socketfd, buffer, 2);
      printf("\n# ");
      memset(buffer, 0, BUFFER_SIZE);
      // if (shouldRead)
      //{
         readInput(buffer, IN_BUF_LIMIT, stdin);
      // printf("Buffer was %lu\n", strlen(buffer));
         numBytes = send(socketfd, buffer, strlen(buffer), 0);
      // fflush(fd);
         if (numBytes < 0)
            die("Couldn't write to socket");
      //}
   }
   close(socketfd);

   return 0;
}
