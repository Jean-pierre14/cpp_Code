#include <iostream>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/ServerSocket.h>

using namespace Poco;
using namespace Poco::Net;

class MyRequestHandler : public HTTPRequestHandler
{
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
    {
        if (request.getMethod() == "GET" && request.getURI() == "/hello")
        {
            response.setChunkedTransferEncoding(true);
            response.setContentType("text/plain");
            std::ostream& ostr = response.send();
            ostr << "Hello, world!";
        }
        else
        {
            response.setStatus(HTTPResponse::HTTP_NOT_FOUND);
            response.setReason("Not Found");
        }
    }
};

int main(int argc, char** argv)
{
    HTTPServer server(new MyRequestHandlerFactory, ServerSocket(8080), new HTTPServerParams);
    server.start();
    std::cout << "Server started" << std::endl;
    server.waitForStop();
    return 0;
}
