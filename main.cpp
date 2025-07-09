#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;

class Stock {
    public:
    string company;
    long marketcap;
    double purchase_price; 

    Stock() {
        
    } 

    Stock(string c, long mkc, double pp) {
        company = c;
        marketcap = mkc;
        int r = rand(); 
        if(r % 2 == 0) {
        purchase_price = purchase_price + r % 100 + 0.224;
        } 
        else {
        purchase_price = purchase_price - r % 100 - 0.224;
        }
    } 
};

class Holdings {
    public:
    string stock;
    int units;
   // vector<Holdings>vec; 

   /* void set_holdings(string s, int u) {
        Holdings h;
        h.stock = s;
        h.units = u;
        vec.push_back(h);
    }*/
};

class Demat_account :public Stock, public Holdings {
    private:
    long account_no;
    string user_name;
    double balance=0;
    bool add_money;

    public:
    vector<Holdings> vec;
    void get_input() {
        cout << "Account No. :" << endl;
        cin >> account_no;
        cout << "Username :" << endl;
        cin >> user_name;
    } 

    void set_holdings(string s, int u) {
        Holdings h;
        h.stock = s;
        h.units = u;
        vec.push_back(h);
    }

    void purchase() {
        int qty;
        cout << "Select a stock to purchase :" << endl;
        cin >> company;
        cout << "Select quantity to purchase :" << endl;
        cin >> qty;
        if((purchase_price*qty) > balance) {
            cout << "Not enough balance to purchase the stock:" << endl;
            cout << "Add money to your account ?(1/0)" << endl;
        cin >> add_money;
        if(add_money==1) {
            double deposit;
            cout << "Select amount to deposit in your demat account : " << endl;
            cin >> deposit;
            balance = balance + deposit;
            cout << "Purchase order executed successfully!" << endl;
            balance = balance - (purchase_price*qty); 
            set_holdings(company, qty); 
        } 
        } 
        else if((purchase_price*qty) < balance){ 
            cout << "Purchase order executed successfully!" << endl;
            balance = balance - (purchase_price*qty); 
            set_holdings(company, qty);
        }  
    }



    void sell() {
        string stock_sell;
        int qty_sell;
        bool check_stock = false;
        Holdings temp;
        cout << "Here are all of your holdings :" << endl << endl;
        for(int i=0; i<vec.size(); i=i+1) {
            cout << "Company :" << vec.at(i).stock << "Units" << vec.at(i).units << endl;
        }
        cout << endl;
        cout << "Select a stock to sell :" << endl;
        cin >> stock_sell;
        for(int i=0; i<vec.size(); i=i+1) {
            if(stock_sell==vec.at(i).stock) {
                check_stock = true;
                temp.stock = vec.at(i).stock;
                temp.units = vec.at(i).units;
            }
        }
        if(check_stock==false) {
            cout << "This stock is not present in your holdings" << endl;
            sell();
        }
        else if(check_stock==true) {
            cout << "Enter its no. of units to sell :" << endl;
            cin >> qty_sell;
            if(qty_sell>temp.units) {
                cout << "You can't sell more no of units than you hold" << endl;
            } 
            else if(qty_sell<=temp.units) {
                balance = balance + (purchase_price*qty_sell); 
                cout << "Sell order successfully executed!" << endl;
                for(int i=0; i<vec.size(); i=i+1) {
                    if(temp.stock==vec.at(i).stock) {
                        vec.at(i).units = vec.at(i).units - qty_sell;
                    } 
                    if(vec.at(i).units==0) {
                        vec.at(i).stock = "NULL";
                    }
                }
            }
        }
    }

    void view_holdings() {
        if(vec.size()==0) {
            cout << "You don't have any investments in your account." << endl;
        } 
        else {
            for(int i=0; i<vec.size(); i=i+1) {
                cout << "Stock :" << vec.at(i).stock << " " << "Units :" << vec.at(i).units << endl; 
            }
        }
    }
    
    void view_balance() {
        cout << "Current demat account balance :" << balance << endl;
    }
}; 

int select() {
    int s;
    cout << "1. Purchase/Buy a stock "<< endl << "2. View your holdings" << endl <<"3. Sell a stock" << "4. View Balance" << endl;
    cout << "Select a choice from the menu" << endl;
    cin >> s;

    return s;
} 

void fluctuation() {
    Stock first("Reliance", 180000000, 2000.45);
    Stock second("HDFCBank", 170000000, 1672.33);
    Stock third("TataMotors", 150000000, 645.603);
    Stock fourth("ICICIBank", 140000000, 1890.92);
    Stock fifth("SunPharma", 120000000, 2444.59);
    Stock sixth("TCS",110000000, 4551.106);
    Stock seventh("Infosys", 90000000, 1372.88);
    Stock eight("NTPC", 70000000, 223.901);
    Stock nineth("Cipla", 65000000, 708.26);
    Stock tenth("MarutiSuzuki", 60000000, 5620.32);
} 

int re_run(Demat_account user1) {
    int operate;
    cout << "Operate on your demat ?" << endl;
    cin >> operate;
    if(operate==1) {

        fluctuation();
        int choice = select();
        if(choice==1) {
            user1.purchase();
        } 
        else if(choice==2) {
            user1.view_holdings();
        }
        else if(choice==3) {
            user1.sell();
        }
        else if(choice==4) {
            user1.view_balance();
        }
        else {
            cout << "Incorrect selection" << endl;
            re_run(user1);
        }

    }
    re_run(user1);
}

int main() { 

    cout << "Stocks : Reliance, HDFCBank, TataMotors, ICICIBank, SunPharma, TCS, Infosys, NTPC, Cipla, MarutiSuzuki" << endl;

    fluctuation();

    Demat_account user1;
    user1.get_input();
    int choice = select();
    if(choice==1) {
        user1.purchase();
    } 
    else if(choice==2) {
        if(user1.vec.size()==0) {
            cout << "You don't have any investments in your account." << endl;
        } 
        else {
            user1.view_holdings();
        }
    } 
    else if(choice==3) {
        if(user1.vec.size()==0) {
            cout << "You don't have any stock holdings to sell." << endl; 
        } 
        else {
            user1.sell();
        }
    } 
    else if(choice==4) {
        user1.view_balance();
    }
    else{
        cout << "Incorrect selection" << endl;
        main();
    }

    // Creating individual company stocks;
    int operate = re_run(user1);
    

    return 0; 
}