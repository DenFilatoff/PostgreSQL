#include <string>
#include <iostream>
#include <pqxx/pqxx>
using namespace std;

string setString () {
string username, password, email, result;	
std::cout << " set Username: \n";
std::cin >> username;
std::cout << " set Password: \n";
std::cin >> password;
std::cout << " set Email: \n";
std::cin >> email;
 result = "INSERT into users values ('" + username + "', '" + password + "', '" + email +  "' );"  ;
std::cout << result  ;
std::cout <<  " \n ";
 return result;
}


void doinsert()  {
std::cout << "Do insert \n";
string insertString = setString();
std::string connectionString = "host=10.129.0.23 port=5000 dbname= postgres user=postgres password = postgres";
 try
    {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);
        pqxx::result response = worker.exec(insertString);
	worker.commit();
	connectionObject.disconnect();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void doread()  {
std::cout << "Do read \n";
 std::string connectionString = "host=10.129.0.23 port=5000 dbname=postgres user=postgres password = postgres";
 try
    {
        pqxx::connection connectionObject(connectionString.c_str());
        pqxx::work worker(connectionObject);
        pqxx::result response = worker.exec("SELECT * FROM users");
        for (size_t i = 0; i < response.size(); i++)
        {
            std::cout << "Id: " << response[i][0] << " Username: " << response[i][1] << " Password: " << response[i][2] << " Email: " << response[i][3] << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "no  Do read \n";
        std::cerr << e.what() << std::endl;
    }
}



int main()
{
char action, again;
bool repeat = true;
while(repeat)  { 
std::cout << "Let's insert [i] or read [r] \n";

std::cin >> action;
if (action == 'i') {doinsert();}
   else {doread();}
 
std::cout << "Do operation again? Please input, yes [y] or no [n] . \n";
 std::cin >> again;
if (again == 'y') { std::cout << "Input was y \n";    ; repeat = true;}
   else { std::cout << "Input was n \n";   ; repeat = false;}
   
}

}




