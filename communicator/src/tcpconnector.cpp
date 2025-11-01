#include "../head/tcpconnector.h"
#include <QMessageBox>
#include <chrono>
#include <thread>


TCPConnector::TCPConnector()
{
    // UtwórZ gniazdo dla tego klienta
    socket_cli = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socket_cli == -1){
       throw TCPException ("Błąd przy tworzeniu gniazda");
    }

    // Utwórz połączenie z serwerem
    memset(&server_conn, '\0', sizeof(server_conn));
    server_conn.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_conn.sin_port = htons( PORT );
    server_conn.sin_family = AF_INET;



    //check if connection is ok
    int connection_flag = connect(socket_cli, (struct sockaddr *) &server_conn, sizeof(server_conn));
    if(connection_flag == -1){
        throw TCPException ("Błąd połączenia z serwerem");
    }


}

TCPConnector::~TCPConnector(){
    close(socket_cli);
}

std::string TCPConnector::Read(std::string _my_id){
    try{
        this->Write( _my_id.append("GET\n").c_str() );
    }catch(TCPException &tcpe){
        QMessageBox::warning(NULL, "Błąd połączenia", tcpe.opis );
    }catch(...){
        std::cerr << "Other error while sending text... " << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    char* buffer;
    std::string wiadomosci = "";
    // tu niby może kilka razy połykać, ale zazwyczaj ssie wszystko na raz
    do{
        buffer = new char[DATA_BLOCK];
        int readErr = read(socket_cli, buffer, DATA_BLOCK);
        if (readErr<0) throw TCPException ("Błąd przy czytaniu odpowiedzi serwera");


        wiadomosci.append(buffer);

    }while(std::string(buffer) == "END");

    wiadomosci.erase( wiadomosci.find("END"), 3 );

    return wiadomosci;
}

int TCPConnector::Write(const std::string _input){
    char* wiad = const_cast<char*>(_input.c_str());
    int n = write( socket_cli, wiad , _input.length()); // ten sizeof zle dziala
    if( n < 0 ){
      throw TCPException ("Błąd przy wysyłaniu danych do serwera");
    }else{
       std::cout << " Sent: " << _input << " of size " << _input.size() << '\n';
    }
    return 0;
}
