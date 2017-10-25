#include "buffer.h"
#include "util.h"
#include "http_help.h"
#include <string.h>
#define SERVER_STRING "Server: gw_httpd/0.1.0\r\n"

int set_http_header_status(Buffer * buffer,int http_status)
{
    //Buffer * buffer = create_buffer(1024);
    char *str="" ;
    switch(http_status)
    {
        case HTTP_200:
          str = "HTTP/1.0 200 OK\r\n";
        break;
        case HTTP_302:
          str = "HTTP/1.0 302 OK\r\n";
        break;
        case HTTP_404:
          str = "HTTP/1.0 404 OK\r\n";
        break;
        case HTTP_503:
          str = "HTTP/1.0 503 OK\r\n";
        break;
    }
   
    write_buffer(buffer,str , strlen(str));

    str = SERVER_STRING;
    write_buffer(buffer,str , strlen(str));

    return 0;
}

int set_http_header_content_type(Buffer *buffer,int content_type)
{
    char *str ="";
    switch(content_type)
    {
        case HTTP_TYPE_HTML:
             str = "text/html; charset=utf-8\r\n";
         break;
        case HTTP_TYPE_JSON:
             str = "Content-Type: application/json\r\n";
         break;
        case HTTP_TYPE_PNG:
             str = "Content-Type: text/html\r\n";
         break;
        default:
            str = "Content-Type: image/png\r\n";
    }
   
    write_buffer(buffer,str , strlen(str));
}

int set_http_header_end(Buffer *buffer)
{
  write_buffer(buffer, "\r\n", strlen("\r\n"));
}

int  send_404_page(int client_sockfd)
{
    Buffer * buffer = create_buffer(1024);
    //send(client, buf, strlen(buf), 0);
    char *str ;
    str = "HTTP/1.0 404 NOT FOUND\r\n";
    write_buffer(buffer,str , strlen(str));

    str = SERVER_STRING;
    write_buffer(buffer,str , strlen(str));

    str = "Content-Type: text/html\r\n";
    write_buffer(buffer,str , strlen(str));

    write_buffer(buffer, "\r\n", strlen("\r\n"));

    str = "<HTML><TITLE>Not Found</TITLE>\r\n";
    write_buffer(buffer,str , strlen(str));

    str = "<BODY><P>The server could not fulfill</P>\r\n";
    write_buffer(buffer, str, strlen(str));

    str = "</BODY></HTML>";
    write_buffer(buffer, str, strlen(str));
   
    write_socket(client_sockfd, buffer->buffer, buffer->pos);
    free_buffer(buffer);
    return 0;
}

int  add_503()
{

}

int  add_302()
{

}
