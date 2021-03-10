#include <iostream>
#include <string>

class BankAccount
{
  private:
    int account_number;
    std::string owner_name;
    double available_funds;
    

  public:
    BankAccount(int account, std::string owner, double funds){
        setOwnerName(owner);
        setAccountNumber(account);
        setAvailableFunds(funds);
    }
      // TODO: declare setters
    void setAccountNumber(int account_number) {
        this->account_number = account_number;
    }
    void setOwnerName(std::string owner_name) {
        this->owner_name = owner_name;
    }
    void setAvailableFunds(double funds) {
        this->available_funds = funds;
    }

    int getAccountNumber(){
        return account_number;
    }
    std::string getOwnerName(){
        return owner_name;
    }
    double getAvailableFunds(){
        return available_funds;
    }
};


int main(){
    BankAccount CarlosBankAccount = BankAccount(10, "Carlos", 0);
    std::cout << CarlosBankAccount.getOwnerName() << "\n";
    std::cout << CarlosBankAccount.getAccountNumber() << "\n";
    std::cout << CarlosBankAccount.getAvailableFunds() << "\n";
    
}