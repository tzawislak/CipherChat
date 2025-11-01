#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>
#include <thread>
#include <map>
#include <regex>
#include <algorithm>

#define DATA_BLOCK 1024

typedef std::vector<std::string>  listy;


std::map<char*, char*> clients;
std::map<std::string, listy > skrzynka;
int shallIstop = 0; // do kończenia wątków
// obecne rozwiązanie nie zawiera timeoutów, więc kończy gdy ktoś nowy spróbuje sie podłączyc
// to nie jest teraz problem, bo serwer ma dzialac w zamiarze do konca swiata.
// dziala i obsluguje kilku użytkownikow na raz


/**
  Funkcja do obsługi nowego klienta
*/
void Connection(struct sockaddr_in* _cli, socklen_t _cliLen, int _accept_status)
{
  // pobiera od klienta jego ID i zapisuje je w mapie, dzięki temu serwer będzie mógł wysłać klientowi wiadomosci od innych.
  char buffer[DATA_BLOCK];
  int id = read( _accept_status,buffer,DATA_BLOCK-1);
  if (id < 0){
      std::cout << "Client " << inet_ntoa(_cli->sin_addr) << " ID error " << std::endl;
      return;
  }
  std::cout<<"Client " << inet_ntoa(_cli->sin_addr) << " : "<< buffer <<std::endl;
  // przyporzadkuj IP do klienta // powinno sprawdzac czy wysłany string to id clienta
  clients[buffer] = inet_ntoa(_cli->sin_addr);
  std::cout << "Klienci: \n";
  for(auto it = clients.begin(); it != clients.end(); ++it)
      std::cout << "\t"<<it->first << "\t" << it->second << "\n";



  // obsługuj klienta dalej
  while (1) {
    if(shallIstop) break;
    char* message = new char[DATA_BLOCK];

    int n = read( _accept_status,message,DATA_BLOCK-1);
    if (n < 0){
        std::cout << "Client " << inet_ntoa(_cli->sin_addr) << " error " << std::endl;
        break;
    }
    //std::regex rgx_ip ("(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)(\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)){3}");
    try{

      std::string RecipientID = std::string(message).substr(0, 6);
      std::string content = std::string(message).substr(6 );
      std::cout<<"Client " << inet_ntoa(_cli->sin_addr) << "\n" << RecipientID << '\n' << content <<std::endl;

      // sprawdz czy to prosba o dane ze skrzynki
      if ( content.substr(0, 3) == "GET"){
        std::cout << "Proba wysłania "  << std::endl;
        listy contact = skrzynka[ RecipientID ];

          for( std::string val : contact){
            char* wiad = const_cast<char*>(val.append("\t").c_str());
            int n = write( _accept_status, wiad, val.length());
            std::cout << "Wysylam: " << val << std::endl;
          }


          int n = write( _accept_status, "END\n", 3);
          std::cout << "Wysylam: " << "END" << std::endl;

          skrzynka[ RecipientID ] = listy();

        continue;
      }
      // jesli to nowa wiadomosc, to dodaj do skrzynki

      skrzynka[ RecipientID ].push_back( std::string(content) );

      for(auto it = skrzynka.begin(); it != skrzynka.end(); ++it){
          for(auto &itt : it->second)
          std::cout << "   "<<it->first << '\t' << itt <<  "\n";
      }
  }catch(...){
    std::cerr << "Message cannot be handled" << std::endl;
    break;
  }

  }
}

/**
  Wątek nawigujący
  Umozliwia zamknięcie programu
*/
void Navigation(){
  while (1) {
    int isEnd;
    std::cin >>isEnd;
    if(isEnd == 0){
      break;
    }
  }
  std::cout << "Server shutting down..." << std::endl;
  shallIstop = 1;
}



int main(int argc, char**argv) {
    // Prints welcome message...
    std::cout << "Welcome To TCP Server..." << std::endl;

    std::map<std::string, std::thread*> mapa_watkow;

    int serverSocket, port=9000, bind_status, listen_status, accept_status;
    socklen_t clientLen;
    struct sockaddr_in server_add, client_add;
    memset(&server_add, '\0', sizeof(server_add));


    // próbuj znaleźć wolny port
    do{
      //check port number
      //check for socket starting error
      serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      if(serverSocket == -1){
          std::cerr << "Server Socket Error... Trying port: "<< port << std::endl;
          std::exit(1);
      }

      server_add.sin_family = AF_INET;
      server_add.sin_addr.s_addr = INADDR_ANY;
      server_add.sin_port = htons(port);

      // check for binding error
      bind_status = bind(serverSocket, (struct sockaddr *) &server_add, sizeof(server_add));
      if(bind_status == -1){
          std::cerr << "Server Binding Error... Trying port: " << port+1 << std::endl;
          port ++;
      }


    // obsługa zapytań
    }while( bind_status == -1 );

    std::thread* tnavig = new std::thread(Navigation);
    tnavig->detach();
    mapa_watkow.insert({"this", tnavig});
    //loop begins
    while(true)
    {
        if(shallIstop){
          std::cout << "KOniec";
          close(serverSocket);
        }

        std::cout<<"Server Waiting for the Client..."<<std::endl;
        listen_status = listen(serverSocket, SOMAXCONN);

        if(listen_status == -1){
            std::cerr << "Server Listening Error "<< std::endl;
            std::exit(1);
        }


        memset(&client_add, '\0', sizeof(client_add));
        clientLen = sizeof(client_add);
        accept_status = accept(serverSocket, (struct sockaddr *) &client_add, &clientLen);

        if(accept_status == -1){
            std::cerr << "Server Accepting Error "<< std::endl;
            std::exit(1);
        }
        // nowy watek
        std::thread* t = new std::thread(Connection, &client_add, clientLen, accept_status);
        t->detach();  // niech dziala, zamiast join()
        mapa_watkow[std::string(inet_ntoa(client_add.sin_addr))] =  t;
        for(auto it = mapa_watkow.begin(); it != mapa_watkow.end(); ++it)
        {
            std::cout << "   "<<it->first << "\n";
        }

    }




    return 0;
}
