#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>

using namespace std;

// 계좌를 나타내는 class
class Account {
private:
	string account_num; // 계좌번호
	string account_user; // 계좌 주인
	int account_balance; // 계좌 잔액
	string account_bank; // 계좌 은행
	int account_password; // 계좌 비밀번호
	string account_transaction; // 계좌 거래내역
	string account_transaction_kor;
public:
	// 생성자 : 계좌번호, 계좌주인, 계좌 잔액, 계좌은행, 계좌 비밀번호를 받고, 계좌 거래내역은 비어있는 채로 시작
	Account(string a_num, string a_user, int a_balance, string a_bank, int a_pw); 
	string account_Num() { return account_num; }; // 계좌번호를 반환
	string account_User() { return account_user; }; // 계좌주인을 반환
	int account_Balance() { return account_balance; }; 	// 계좌 잔액을 반환
	string account_Bank() { return account_bank; }// 계좌 거래내역을 반환
	string account_Transaction() { return account_transaction; };
	int account_Password() { return account_password; }; // 계좌 비밀번호를 반환
	// 계좌에 d만큼 입금
	void account_Deposit(int d) { account_balance += d; };
	// 계좌에서 w만큼 출금
	void account_Withdrawl(int w) { account_balance -= w; };
	// 계좌 거래내역 추가
	void transaction_Add(string eng, string kor) { account_transaction += eng; account_transaction_kor += kor; };
	string ret_transac_history(bool is_eng);
};

Account::Account(string a_num, string a_user, int a_balance, string a_bank, int a_pw) {
	// 입력받은 값들로 초기화
	account_num = a_num; account_user = a_user; account_balance = a_balance; account_bank = a_bank; account_password = a_pw;
	account_transaction = "", account_transaction_kor = "";
}

string Account::ret_transac_history(bool is_eng) {
	if (is_eng == true) {
		return account_transaction;
	}
	else {
		return account_transaction_kor;
	}
}

// 계좌와 연결된 카드를 나타내는 class
class Card {
private:
	string account_num;// Card의 Account num
	string bank_name; // Card의 Bank 이름을 string으로 저장 : admin의 경우 admin으로 저장
	bool is_admin; // admin 여부를 나타냄
public:
	// 생성자 
	Card(string a_num, string b_name, bool is_Admin);
	bool is_Admin() { return is_admin; } // admin 여부를 반환 
	string account_Num() { return account_num; }// Account pointer를 반환
	string bank_Name() { return bank_name; }
};

Card::Card(string a_num, string b_name, bool is_Admin) {
	account_num = a_num;
	bank_name = b_name;
	is_admin = is_Admin;
}


// 은행을 나타내는 class
class Bank {
private:
	string bank_name; // Bank의 이름을 나타낸다.
	Account** bank_accounts; // 은행이 발급한 Account pointer array
	static int max_bank_accounts; // bank_accouts의 최대 계좌 수 : static
	int bank_accounts_Lastindex = -1; // bank_accounts의 마지막 인덱스 >> -1로 한건 최초 값 부여시 코드를 간단히 작성하기 위함.
	Bank** another_banks; // 다른 Bank pointer array
	static int max_another_banks; // another_banks의 최대 수 : static
	int another_banks_Lastindex = -1; // another_banks의 마지막 인덱스
	static Account zeroAccount; // 빈 account를 static으로 선언
public:
	Bank(string b_name); // 생성자 : bank_name을 정하고, bank_accounts, another_banks, bank_atms 를 동적할당으로 만들기
	~Bank(); // 소멸자 : 동적할당된 bank_accounts, another_banks, bank_atms를 delete하기
	string bank_Name() { return bank_name; }; // Bank 이름을 반환
	Card* create_Account(string a_num, string a_user, int a_balance, int a_pw); // Account를 발급하고 Account의 Card pointer를 반환한다.
	Card* create_Admin();
	void add_Bank(Bank* another_b); // 다른 Bank pointer를 받아서 another_banks에 넣는다.
	// 내 bank_accounts에서 a_num 계좌번호를 가진 Account가 있는지 찾는다. 있으면 Account pointer 반환, 없으면 nullptr 반환
	Account* search_myAccount(string a_num);
	Account* search_anotherAccount(string a_num);
	bool user_Authorize(Account* a, int pw); // 유저가 입력한 비밀번호가 맞는지 확인하고 그 결과를 bool로 반환
	Account* ret_zeroAccount() { return &(Bank::zeroAccount); }
	void print_account_Remainbalance();
};

// static 변수들을 초기화
int Bank::max_bank_accounts = 10;
int Bank::max_another_banks = 10;
Account Bank::zeroAccount = Account("Zero", "Zero", 0, "Zero", 0);

Bank::Bank(string b_name) {
	bank_name = b_name;
	// 동적 할당으로 array 만들기
	bank_accounts = new Account * [max_bank_accounts];
	another_banks = new Bank * [max_another_banks];
}

Bank::~Bank() {
	// 동적할당 된 것들 다 동적할당 해제
	for (int i = 0; i <= bank_accounts_Lastindex; i++) {
		delete bank_accounts[i];
	}
	for (int i = 0; i <= another_banks_Lastindex; i++) {
		delete another_banks[i];
	}
	delete[] bank_accounts;
	delete[] another_banks;
}

Card* Bank::create_Account(string a_num, string a_user, int a_balance, int a_pw) {
	// bank_accounts_Lastindex에 1을 더함
	bank_accounts_Lastindex += 1;
	// 입력받은 정보로 새 Account를 만듬
	bank_accounts[bank_accounts_Lastindex] = new Account(a_num, a_user, a_balance, bank_Name(), a_pw);
	// 새로만든 Account에 해당하는 Card를 만들고 추후 반환
	Card* return_card = new Card(bank_accounts[bank_accounts_Lastindex]->account_Num(), bank_accounts[bank_accounts_Lastindex]->account_Bank(), false);
	return return_card;
}

Card* Bank::create_Admin() {
	Card* ret_card = new Card("admin", bank_Name(), true);
	return ret_card;
}

void Bank::add_Bank(Bank* another_b) {
	// another_banks_Lastindex에 1을 더함
	another_banks_Lastindex += 1;
	// 입력받은 다른 Bank의 주소를 집어넣음
	another_banks[another_banks_Lastindex] = another_b;
}

Account* Bank::search_myAccount(string a_num) {
	// 일단 자기 은행 계좌에서 검색
	for (int i = 0; i <= bank_accounts_Lastindex; i++) {
		if (bank_accounts[i]->account_Num() == a_num) {
			return bank_accounts[i];
		}
	}
	// for 문을 다 돌아도 없으니 zeroAccount를 반환
	return &(Bank::zeroAccount);
}

Account* Bank::search_anotherAccount(string a_num) {
	// 다른 은행에서 검색
	for (int i = 0; i <= another_banks_Lastindex; i++) {
		Account* temp_account = another_banks[i]->search_myAccount(a_num);
		if (temp_account->account_Num() == a_num) {
			return temp_account;
		}
	}
	// for문이 끝났다는거는 다른 은행에도 없다는 뜻이니 zeroAccount 반환
	return &(Bank::zeroAccount);
}

bool Bank::user_Authorize(Account* a, int pw) {
	if (a->account_Password() == pw) {
		return true;
	}
	else {
		return false;
	}
}

void Bank::print_account_Remainbalance() {
	cout << "[" + bank_name + "Account Balance]" << endl;
	for (int i = 0; i <= bank_accounts_Lastindex; i++) {
		cout << bank_accounts[i]->account_User() + "'s Account " + bank_accounts[i]->account_Num() + " Balance : " + to_string(bank_accounts[i]->account_Balance()) << endl;
	}
}

// ATM 기계를 나타내는 class
class Atm {
protected:
	int atm_serial; // Atm의 시리얼번호를 저장하는 곳
	Bank* primary_bank; // primary bank를 저장하는 곳
	bool is_ul; // Uni Lingual 여부를 bool로 저장
	int left_cash[4]; // Atm에 남아있는 천원, 오천원, 만원, 오만원 권이 각각 얼마가 있는가를 저장하는 int array
	string transac_history = ""; // Atm기에서 이때까지 있었던 거래기록들을 저장하는 곳
	string transac_history_kor = ""; // 한국어 거래기록
	int getable_cash_num = 50; // Atm기에서 한번에 받을 수 있는 cash의 양을 정하는 변수
	int getable_check_num = 30; // Atm기에서 한번에 받을 수 있는 chek의 양을 정하는 변수
	int withdrawal_amount = 500000; // Atm기에서 한번에 출금할 수 있는 금액 양.
	int called_session_num = 0; // 세션이 이때까지 불려진 횟수
	int max_withdrawal = 3; // 세션당 최대로 출금가능한 횟수
	// 수수료
	int fee_deposit_non_primary = 1000;
	int fee_deposit_primary = 0;
	int fee_withdrawal_primary = 1000;
	int fee_withdrawal_non_primary = 2000;
	int fee_transfer_primary_primary = 2000;
	int fee_transfer_primary_non_primary = 3000;
	int fee_transfer_non_primary_non_primary = 4000;
public:
	// 생성자는 상속받는 class에서 구현해야 하니 여기서는 생략한다.
	// 상속받는 class에 따라 다르게 구현되는 모든 메소드들은 virtual function으로 정의한다.
	// 반환값 또한 어떻게 구현하는지에 따라 달라질 수 있다는 점을 염두해둬야 한다.

	// Transac_history에 거래내역을 기록한다.
	void write_Transac_history(string eng, string kor);
	void print_Leftcash();
	virtual int Deposit(Account* a) = 0; // 입금을 구현 : a에서 m만큼 입금
	virtual int Withdrawal(Account* a) = 0; // 출금을 구현 : a에서 m만큼 출금
	virtual int Transfer(Account* a1, Account* a2) = 0; // 송금을 구현 : a1에서 a2에게 m만큼 송금
	virtual bool user_Authorize(Account* a) = 0; // 입력받은 비밀번호를 체크하는 부분. 맞으면 True, 세 번 이상 틀리면 False를 반환
	// 이 아래 함수들은 추후 함수에서 활용되므로 virtual로 정의해놓는다.
	virtual int Deposit_Kor(Account* a) = 0;
	virtual int Withdrawal_Kor(Account* a) = 0;
	virtual int Transfer_Kor(Account* a1, Account* a2) = 0;
	virtual bool user_Authorize_Kor(Account* a) = 0;
	//session
	virtual void session_Start(Card* c) = 0;
	virtual void session_Main(Card* c) = 0;
	virtual void session_Main_Kor(Card* c) = 0;
	virtual void session_Admin(Card* c) = 0;
	virtual void session_Admin_Kor(Card* c) = 0;
};

void Atm::write_Transac_history(string eng, string kor) {
	transac_history += eng;
	transac_history_kor += kor;
}

void Atm::print_Leftcash() {
	string output = "[" + primary_bank->bank_Name() + " ATM " + to_string(atm_serial) + "] Remaining cash : "
		+ to_string(1000 * left_cash[0] + 5000 * left_cash[1] + 10000 * left_cash[2] + 50000 * left_cash[3]);
	cout << output << endl;
}

// Single Bank Atm을 나타내는 class : Atm에서 상속됨
class Atm_SingleBank : public Atm {
public:
	// 생성자 : 시리얼번호, Primary Bank, SBA, UL 여부를 입력받음
	Atm_SingleBank(int a_serial, Bank* p_bank, bool ul, int* If_cash);
	// 현금을 받거나 줄때는 금액 종류별로 몇장을 받을 건지 물어보자. 재고 반영은 몇장씩 주고 받는 걸로 해결.
	// 입금을 구현 : a에서 m만큼 입금 : 표시되는 언어는 영어다
	int Deposit(Account* a);
	// 출금을 구현 : a에서 m만큼 출금 : 표시되는 언어는 영어다
	int Withdrawal(Account* a);
	// 송금을 구현 : a1에서 a2에게 m만큼 송금 : 표시되는 언어는 영어다.
	int Transfer(Account* a1, Account* a2);
	// 입력받은 비밀번호를 체크하는 부분. 맞으면 True, 세 번 이상 틀리면 False를 반환 : 표시되는 언어는 영어다.
	bool user_Authorize(Account* a);
	// 입금을 구현 : a에서 m만큼 입금 : 표시되는 언어는 한국다
	int Deposit_Kor(Account* a);
	// 출금을 구현 : a에서 m만큼 출금 : 표시되는 언어는 한국어다
	int Withdrawal_Kor(Account* a);
	// 송금을 구현 : a1에서 a2에게 m만큼 송금 : 표시되는 언어는 한국어다.
	int Transfer_Kor(Account* a1, Account* a2);
	// 입력받은 비밀번호를 체크하는 부분. 맞으면 True, 세 번 이상 틀리면 False를 반환 : 표시되는 언어는 한국어다.
	bool user_Authorize_Kor(Account* a);
	// session 
	void session_Start(Card* c);
	void session_Main(Card* c);
	void session_Main_Kor(Card* c);
	// admin일 경우 다른 세션을 불러온다. 
	void session_Admin(Card* c);
	void session_Admin_Kor(Card* c);
};

Atm_SingleBank::Atm_SingleBank(int a_serial, Bank* p_bank, bool ul, int* lf_cash) {
	atm_serial = a_serial;
	primary_bank = p_bank;
	is_ul = ul;
	for (int i = 0; i < 4; i++) {
		left_cash[i] = lf_cash[i];
	}
}

int Atm_SingleBank::Deposit(Account* a) {
	int button{ 0 }; // 메뉴 선택 버튼
	// 현금 입력 시 지폐 별 개수 저장, 수표 개수 저장
	int won_1{ 0 }, won_5{ 0 }, won_10{ 0 }, won_50{ 0 }, num_of_check{ 0 };
	int total_amount{ 0 }; // 총 투입 금액
	// 예외 발생 시 처음 Deposit 상태로 돌아오기 위해 무한 루프로 구현
	while (1) {
		cout << "======================================" << endl;
		cout << "Select type of money" << endl;
		cout << "Select a number" << endl;
		cout << "======================================" << endl;
		cout << "|  1. Cash  |  2. Check  |  3. Exit  |" << endl;
		cout << "======================================" << endl;
		cin >> button;
		// Cash 선택 시
		if (button == 1) {
			cout << "======================================" << endl;
			cout << "Please enter the number of bills" << endl;
			cout << "You can put up to " + to_string(this->getable_cash_num) + " bills." << endl;
			cout << "======================================" << endl;
			cout << "Enter num of KRW 1,000 :";
			cin >> won_1;
			cout << "Enter num of KRW 5,000 :";
			cin >> won_5;
			cout << "Enter num of KRW 10,000 :";
			cin >> won_10;
			cout << "Enter num of KRW 50,000 :";
			cin >> won_50;
			cout << "======================================" << endl;
			// ATM이 수용 가능한 지폐 개수 초과시 에러 메세지 출력 및 Deposit 재실행
			if (won_1 + won_5 + won_10 + won_50 > this->getable_cash_num) {
				button = won_1 = won_5 = won_10 = won_50 = 0;
				cout << "======================================" << endl;
				cout << "Error : The total number of bills accepted has been exceeded" << endl;
				cout << "======================================" << endl;
				continue;
			}
			// ATM 지폐 개수 및 Account 잔액 update
			total_amount = 1000 * won_1 + 5000 * won_5 + 10000 * won_10 + 50000 * won_50;
			cout << "======================================" << endl;
			cout << "A fee of KRW " + to_string(this->fee_deposit_primary) + " was incurred" << endl;
			cout << "======================================" << endl;
			if (total_amount < this->fee_deposit_primary) {
				cout << "======================================" << endl;
				cout << "Error : Insufficient account balance" << endl;
				cout << "======================================" << endl;
				button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
				continue;
			}
			a->account_Deposit(total_amount - this->fee_deposit_primary);
			this->left_cash[0] += won_1;
			this->left_cash[1] += won_5;
			this->left_cash[2] += won_10;
			this->left_cash[3] += won_50;
			return total_amount - this->fee_deposit_primary;
		}
		// Check 선택 시
		else if (button == 2) {
			cout << "======================================" << endl;
			cout << "Please enter the amount of check" << endl;
			cout << "======================================" << endl;
			cout << "amount of check : ";
			cin >> total_amount;
			cout << "======================================" << endl;
			cout << "Please enter the number of check" << endl;
			cout << "You can put up to " + to_string(this->getable_check_num) + " checks." << endl;
			cout << "======================================" << endl;
			cout << "num of check :";
			cin >> num_of_check;
			// ATM이 수용 가능한 지폐 개수 초과시 에러 메세지 출력 및 Deposit 재실행
			if (num_of_check > this->getable_check_num) {
				total_amount = 0;
				num_of_check = 0;
				button = 0;
				cout << "======================================" << endl;
				cout << "Error : The total number of checks accepted has been exceeded" << endl;
				cout << "======================================" << endl;
				continue;
			}
			// Account 잔액 update
			total_amount = total_amount * num_of_check;
			cout << "======================================" << endl;
			cout << "A fee of KRW " + to_string(this->fee_deposit_primary) + " was incurred" << endl;
			cout << "======================================" << endl;
			if (total_amount < this->fee_deposit_primary) {
				cout << "======================================" << endl;
				cout << "Error : Insufficient account balance" << endl;
				cout << "======================================" << endl;
				button = total_amount = num_of_check = 0;
				continue;
			}
			a->account_Deposit(total_amount - this->fee_deposit_primary);
			return total_amount - this->fee_deposit_primary;
		}
		// Exit 선택 시 
		else if (button == 3) {
			cout << "======================================" << endl;
			cout << "Exit Deposit" << endl;
			cout << "======================================" << endl;
			return -1;
		}
		// 그 외 다른 button이 눌렸을 시 에러 메시지 출력 및 Deposit 재실행
		else {
			cout << "======================================" << endl;
			cout << "Error : Invalid Input" << endl;
			cout << "Please select type of money again" << endl;
			cout << "======================================" << endl;
			continue;
		}
	}
}

int Atm_SingleBank::Withdrawal(Account* a) {
	int button{ 0 };
	// 출금하고자 하는 지폐 별 개수 저장
	int won_1{ 0 }, won_5{ 0 }, won_10{ 0 }, won_50{ 0 };
	int total_amount{ 0 }; // 총 출금 금액
	int ATM_amount = 1000 * this->left_cash[0] + 5000 * this->left_cash[1] + 10000 * this->left_cash[2] + 50000 * this->left_cash[3];
	int amount{ 0 };
	// 예외 발생 시 처음 Withdrawal 상태로 돌아오기 위해 무한 루프로 구현
	while (1) {
		cout << "Withdrawal Menu" << endl;
		cout << "=========================" << endl;
		cout << "|  1. Start |  2. Exit  |" << endl;
		cout << "=========================" << endl;
		cin >> button;
		if (button == 1) {
			cout << "======================================" << endl;
			cout << "Please enter the amount of money(ATM balance : KRW " + to_string(ATM_amount) + ")" << endl;
			cout << "You can withdraw up to KRW " + to_string(this->withdrawal_amount) + " at one time." << endl;
			cout << "======================================" << endl;
			cout << "amount of money :";
			cin >> total_amount;
			if (total_amount > ATM_amount) {
				cout << "======================================" << endl;
				cout << "Error : The ATM balance is insufficient to withdraw money" << endl;
				cout << "======================================" << endl;
				button = total_amount = 0;
				continue;
			}
			if (total_amount > this->withdrawal_amount) {
				cout << "======================================" << endl;
				cout << "Error : You have exceeded the amount that can be withdrawn at one time" << endl;
				cout << "======================================" << endl;
				button = total_amount = 0;
				continue;
			}
			cout << "======================================" << endl;
			cout << "Please enter the number of bills" << endl;
			cout << "You can take out KRW 1,000 bills up to " + to_string(this->left_cash[0]) << endl;
			cout << "You can take out KRW 5,000 bills up to " + to_string(this->left_cash[1]) << endl;
			cout << "You can take out KRW 10,000 bills up to " + to_string(this->left_cash[2]) << endl;
			cout << "You can take out KRW 50,000 bills up to " + to_string(this->left_cash[3]) << endl;
			cout << "======================================" << endl;
			cout << "Enter num of KRW 1,000 :";
			cin >> won_1;
			cout << "Enter num of KRW 5,000 :";
			cin >> won_5;
			cout << "Enter num of KRW 10,000 :";
			cin >> won_10;
			cout << "Enter num of KRW 50,000 :";
			cin >> won_50;
			cout << "======================================" << endl;
			if ((won_1 > this->left_cash[0]) || (won_5 > this->left_cash[1]) || (won_10 > this->left_cash[2]) || (won_50 > this->left_cash[3])) {
				cout << "======================================" << endl;
				cout << "Error : The requested number of bills cannot be withdrawn." << endl;
				cout << "======================================" << endl;
				button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
				continue;
			}
			amount = won_1 * 1000 + won_5 * 5000 + won_10 * 10000 + won_50 * 50000;
			if (total_amount != amount) {
				cout << "======================================" << endl;
				cout << "Error : It does not match the amount you wish to withdraw." << endl;
				cout << "======================================" << endl;
				button = total_amount = amount = won_1 = won_5 = won_10 = won_50 = 0;
				continue;
			}
			cout << "======================================" << endl;
			cout << "A fee of KRW " + to_string(this->fee_withdrawal_primary) + " was incurred" << endl;
			cout << "======================================" << endl;
			if (total_amount + this->fee_withdrawal_primary > a->account_Balance()) {
				cout << "======================================" << endl;
				cout << "Error : Insufficient account balance" << endl;
				cout << "======================================" << endl;
				button = total_amount = amount = won_1 = won_5 = won_10 = won_50 = 0;
				continue;
			}
			a->account_Withdrawl(total_amount + this->fee_withdrawal_primary);
			this->left_cash[0] -= won_1;
			this->left_cash[1] -= won_5;
			this->left_cash[2] -= won_10;
			this->left_cash[3] -= won_50;
			return total_amount;
		}
		else if (button == 2) {
			cout << "======================================" << endl;
			cout << "Exit Withdrawal" << endl;
			cout << "======================================" << endl;
			return -1;
		}
		else {
			cout << "======================================" << endl;
			cout << "Error : Invalid Input" << endl;
			cout << "Please select menu again" << endl;
			cout << "======================================" << endl;
			continue;
		}
	}
}

int Atm_SingleBank::Transfer(Account* a1, Account* a2) {
	int button{ 0 }; // 메뉴 선택 버튼
	int verify_button{ 0 }; // 현금 송금 확인 버튼
	// 현금 입력 시 지폐 별 개수 저장, 수표 개수 저장
	int won_1{ 0 }, won_5{ 0 }, won_10{ 0 }, won_50{ 0 };
	int total_amount{ 0 }; // 총 투입 금액
	// 예외 발생 시 처음 Deposit 상태로 돌아오기 위해 무한 루프로 구현
	while (1) {
		// Transfer을 시작할지 안할지 선택
		cout << "======================================" << endl;
		cout << "Select type of transfer" << endl;
		cout << "Select a number" << endl;
		cout << "=======================================================" << endl;
		cout << "|  1. Cash Transfer |  2. Bank Transfer  |  3. Exit  |" << endl;
		cout << "=======================================================" << endl;
		cin >> button;
		// Cash 선택 시
		if (button == 1) {
			cout << "======================================" << endl;
			cout << "Please enter the number of bills" << endl;
			cout << "You can put up to " + to_string(this->getable_cash_num) + " bills." << endl;
			cout << "======================================" << endl;
			cout << "Enter num of KRW 1,000 :";
			cin >> won_1;
			cout << "Enter num of KRW 5,000 :";
			cin >> won_5;
			cout << "Enter num of KRW 10,000 :";
			cin >> won_10;
			cout << "Enter num of KRW 50,000 :";
			cin >> won_50;
			cout << "======================================" << endl;
			// ATM이 수용 가능한 지폐 개수 초과시 에러 메세지 출력 및 Deposit 재실행
			if (won_1 + won_5 + won_10 + won_50 > this->getable_cash_num) {
				button = won_1 = won_5 = won_10 = won_50 = 0;
				cout << "======================================" << endl;
				cout << "Error : The total number of bills accepted has been exceeded" << endl;
				cout << "======================================" << endl;
				continue;
			}
			// ATM 지폐 개수 및 Account 잔액 update
			total_amount = 1000 * won_1 + 5000 * won_5 + 10000 * won_10 + 50000 * won_50;
			cout << "Would you like to transfer KRW " + to_string(total_amount) << endl;
			cout << "========================" << endl;
			cout << "|  1. Yes  |  2. No  |" << endl;
			cout << "========================" << endl;
			cin >> verify_button;
			if (verify_button != 1) {
				verify_button = button = won_1 = won_5 = won_10 = won_50 = 0;
				cout << "Go back to the beginning menu" << endl;
				continue;
			}
			// a2 은행이 primary bank인 경우
			if (this->primary_bank->bank_Name() == a2->account_Bank()) {
				cout << "======================================" << endl;
				cout << "A fee of KRW " + to_string(this->fee_transfer_primary_primary) + " was incurred" << endl;
				cout << "======================================" << endl;
				// ATM에 투입한 금액이 수수료보다 작을 때
				if (total_amount < this->fee_transfer_primary_primary) {
					cout << "======================================" << endl;
					cout << "Error : The amount is less than the fee" << endl;
					cout << "======================================" << endl;
					button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
					continue;
				}
				a2->account_Deposit(total_amount - this->fee_transfer_primary_primary);
				this->left_cash[0] += won_1;
				this->left_cash[1] += won_5;
				this->left_cash[2] += won_10;
				this->left_cash[3] += won_50;
				return total_amount - this->fee_transfer_primary_primary;
			}
			// a2 은행이 another bank인 경우
			else {
				cout << "======================================" << endl;
				cout << "A fee of KRW " + to_string(this->fee_transfer_primary_non_primary) + " was incurred" << endl;
				cout << "======================================" << endl;
				// ATM에 투입한 금액이 수수료보다 작을 때
				if (total_amount < this->fee_transfer_primary_non_primary) {
					cout << "======================================" << endl;
					cout << "Error : The amount is less than the fee" << endl;
					cout << "======================================" << endl;
					button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
					continue;
				}
				a2->account_Deposit(total_amount - this->fee_transfer_primary_non_primary);
				this->left_cash[0] += won_1;
				this->left_cash[1] += won_5;
				this->left_cash[2] += won_10;
				this->left_cash[3] += won_50;
				return total_amount - this->fee_transfer_primary_non_primary;
			}
		}
		// Bank 선택 시
		else if (button == 2) {
			cout << "======================================" << endl;
			cout << "Please enter the amount of money" << endl;
			cout << "======================================" << endl;
			cout << "amount of money : ";
			cin >> total_amount;
			// a2 은행이 primary bank인 경우
			if (this->primary_bank->bank_Name() == a2->account_Bank()) {
				cout << "======================================" << endl;
				cout << "A fee of KRW " + to_string(this->fee_transfer_primary_primary) + " was incurred" << endl;
				cout << "======================================" << endl;
				// 송금 금액과 수수료 합이 계좌 잔액보다 클때
				if (total_amount + this->fee_transfer_primary_primary > a1->account_Balance()) {
					cout << "======================================" << endl;
					cout << "Error : The sum of the withdrawal amount and fee exceeds account balance" << endl;
					cout << "======================================" << endl;
					button = total_amount = 0;
					continue;
				}
				a1->account_Withdrawl(total_amount + this->fee_transfer_primary_primary);
				a2->account_Deposit(total_amount);
				return total_amount;
			}
			// a2 은행이 another bank인 경우
			else {
				cout << "======================================" << endl;
				cout << "A fee of KRW " + to_string(this->fee_transfer_primary_non_primary) + " was incurred" << endl;
				cout << "======================================" << endl;
				// 송금 금액과 수수료 합이 계좌 잔액보다 클때
				if (total_amount + this->fee_transfer_primary_non_primary > a1->account_Balance()) {
					cout << "======================================" << endl;
					cout << "Error : The sum of the withdrawal amount and fee exceeds account balance" << endl;
					cout << "======================================" << endl;
					button = total_amount = 0;
					continue;
				}
				a1->account_Withdrawl(total_amount + this->fee_transfer_primary_non_primary);
				a2->account_Deposit(total_amount);
				return total_amount;
			}
		}
		// Exit 선택 시 
		else if (button == 3) {
			cout << "======================================" << endl;
			cout << "Exit Transfer" << endl;
			cout << "======================================" << endl;
			return -1;
		}
		// 그 외 다른 button이 눌렸을 시 에러 메시지 출력 및 Deposit 재실행
		else {
			cout << "======================================" << endl;
			cout << "Error : Invalid Input" << endl;
			cout << "Please select type of transfer again" << endl;
			cout << "======================================" << endl;
			continue;
		}
	}
}

bool Atm_SingleBank::user_Authorize(Account* a) {
	int pw{ 0 };
	int wrong_count{ 3 };
	while (1) {
		cout << "======================================" << endl;
		cout << "Please enter a password :";
		cin >> pw;
		cout << "======================================" << endl;
		if (pw != a->account_Password()) {
			pw = 0;
			wrong_count -= 1;
			cout << "======================================" << endl;
			cout << "Error : Incorrect password" << endl;
			cout << "======================================" << endl;
			if (wrong_count == 0) {
				cout << "======================================" << endl;
				cout << "You have no more chances left" << endl;
				cout << "======================================" << endl;
				return false;
			}
			cout << "======================================" << endl;
			cout << "You have " + to_string(wrong_count) + " chances left." << endl;
			cout << "======================================" << endl;
			continue;
		}
		return true;
	}
}

int Atm_SingleBank::Deposit_Kor(Account* a) {
	int button{ 0 }; // 메뉴 선택 버튼
	// 현금 입력 시 지폐 별 개수 저장, 수표 개수 저장
	int won_1{ 0 }, won_5{ 0 }, won_10{ 0 }, won_50{ 0 }, num_of_check{ 0 };
	int total_amount{ 0 }; // 총 투입 금액
	// 예외 발생 시 처음 Deposit 상태로 돌아오기 위해 무한 루프로 구현
	while (1) {
		cout << "======================================" << endl;
		cout << "입금하고자 하는 돈의 유형을 선택하세요" << endl;
		cout << "메뉴 선택은 번호를 입력해주세요" << endl;
		cout << "======================================" << endl;
		cout << "|  1. 현금  |  2. 수표  |  3. 나가기  |" << endl;
		cout << "======================================" << endl;
		cin >> button;
		// Cash 선택 시
		if (button == 1) {
			cout << "======================================" << endl;
			cout << "입금하고자 하는 현금의 지폐수를 입력해주세요" << endl;
			cout << "한 번에 최대 " + to_string(this->getable_cash_num) + " 장까지 처리 가능합니다" << endl;
			cout << "======================================" << endl;
			cout << "1,000원 장수를 입력하세요 :";
			cin >> won_1;
			cout << "5,000원 장수를 입력하세요 :";
			cin >> won_5;
			cout << "10,000원 장수를 입력하세요 :";
			cin >> won_10;
			cout << "50,000원 장수를 입력하세요 :";
			cin >> won_50;
			cout << "======================================" << endl;
			// ATM이 수용 가능한 지폐 개수 초과시 에러 메세지 출력 및 Deposit 재실행
			if (won_1 + won_5 + won_10 + won_50 > this->getable_cash_num) {
				button = won_1 = won_5 = won_10 = won_50 = 0;
				cout << "======================================" << endl;
				cout << "오류 : ATM이 한 번에 처리할 수 있는 지폐의 장수를 초과하였습니다" << endl;
				cout << "======================================" << endl;
				continue;
			}
			// ATM 지폐 개수 및 Account 잔액 update
			total_amount = 1000 * won_1 + 5000 * won_5 + 10000 * won_10 + 50000 * won_50;
			cout << "======================================" << endl;
			cout << "수수료가 " + to_string(this->fee_deposit_primary) + "원 발생했습니다" << endl;
			cout << "======================================" << endl;
			if (total_amount < this->fee_deposit_primary) {
				cout << "======================================" << endl;
				cout << "오류 : 입금 금액이 수수료보다 작습니다." << endl;
				cout << "======================================" << endl;
				button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
				continue;
			}
			a->account_Deposit(total_amount - this->fee_deposit_primary);
			this->left_cash[0] += won_1;
			this->left_cash[1] += won_5;
			this->left_cash[2] += won_10;
			this->left_cash[3] += won_50;
			return total_amount - this->fee_deposit_primary;
		}
		// Check 선택 시
		else if (button == 2) {
			cout << "======================================" << endl;
			cout << "입금하고자 하는 수표의 액수를 입력하세요" << endl;
			cout << "======================================" << endl;
			cout << "수표 액수 : ";
			cin >> total_amount;
			cout << "======================================" << endl;
			cout << "입금하고자 하는 수표의 장수를 입력하세요" << endl;
			cout << "한 번에 최대 " + to_string(this->getable_check_num) + " 장의 수표가 처리 가능합니다" << endl;
			cout << "======================================" << endl;
			cout << "수표 장수 :";
			cin >> num_of_check;
			// ATM이 수용 가능한 지폐 개수 초과시 에러 메세지 출력 및 Deposit 재실행
			if (num_of_check > this->getable_check_num) {
				total_amount = 0;
				num_of_check = 0;
				button = 0;
				cout << "======================================" << endl;
				cout << "오류 : ATM이 한 번에 처리할 수 있는 수표의 장수를 초과하였습니다." << endl;
				cout << "======================================" << endl;
				continue;
			}
			// Account 잔액 update
			total_amount = total_amount * num_of_check;
			cout << "======================================" << endl;
			cout << "수수료가 " + to_string(this->fee_deposit_primary) + "원 발생했습니다" << endl;
			cout << "======================================" << endl;
			if (total_amount < this->fee_deposit_primary) {
				cout << "======================================" << endl;
				cout << "오류 : 입금 금액이 수수료보다 작습니다." << endl;
				cout << "======================================" << endl;
				button = total_amount = num_of_check = 0;
				continue;
			}
			a->account_Deposit(total_amount - this->fee_deposit_primary);
			return total_amount - this->fee_deposit_primary;
		}
		// Exit 선택 시 
		else if (button == 3) {
			cout << "======================================" << endl;
			cout << "입금 메뉴를 종료합니다." << endl;
			cout << "======================================" << endl;
			return -1;
		}
		// 그 외 다른 button이 눌렸을 시 에러 메시지 출력 및 Deposit 재실행
		else {
			cout << "======================================" << endl;
			cout << "오류 : 잘못된 입력입니다" << endl;
			cout << "돈의 유형을 다시 입력해주세요" << endl;
			cout << "======================================" << endl;
			continue;
		}
	}
}

int Atm_SingleBank::Withdrawal_Kor(Account* a) {
	int button{ 0 };
	// 출금하고자 하는 지폐 별 개수 저장
	int won_1{ 0 }, won_5{ 0 }, won_10{ 0 }, won_50{ 0 };
	int total_amount{ 0 }; // 총 출금 금액
	int ATM_amount = 1000 * this->left_cash[0] + 5000 * this->left_cash[1] + 10000 * this->left_cash[2] + 50000 * this->left_cash[3];
	int amount{ 0 };
	// 예외 발생 시 처음 Withdrawal 상태로 돌아오기 위해 무한 루프로 구현
	while (1) {
		cout << "======================================" << endl;
		cout << "출금 유형을 선택하세요" << endl;
		cout << "번호를 입력하세요" << endl;
		cout << "=========================" << endl;
		cout << "|  1. 시작 |  2. 나가기  |" << endl;
		cout << "=========================" << endl;
		cin >> button;
		if (button == 1) {
			cout << "======================================" << endl;
			cout << "출금 금액을 입력해주세요(ATM 보유잔액 : " + to_string(ATM_amount) + " 원)" << endl;
			cout << "한 번에 최대 " + to_string(this->withdrawal_amount) + "원 출금 가능합니다";
			cout << "======================================" << endl;
			cout << "출금 금액 :";
			cin >> total_amount;
			if (total_amount > ATM_amount) {
				cout << "======================================" << endl;
				cout << "오류 : ATM 보유잔액이 부족합니다." << endl;
				cout << "======================================" << endl;
				button = total_amount = 0;
				continue;
			}
			if (total_amount > this->withdrawal_amount) {
				cout << "======================================" << endl;
				cout << "오류 : 한 번에 출금 가능한 금액을 초과하였습니다" << endl;
				cout << "======================================" << endl;
				button = total_amount = 0;
				continue;
			}
			cout << "======================================" << endl;
			cout << "출금을 원하시는 각 지폐별 개수를 선택해주세요" << endl;
			cout << "1,000원은 최대 " + to_string(this->left_cash[0]) + "장 출금가능" << endl;
			cout << "5,000원은 최대 " + to_string(this->left_cash[1]) + "장 출금가능" << endl;
			cout << "10,000원은 최대 " + to_string(this->left_cash[2]) + "장 출금가능" << endl;
			cout << "50,000원은 최대 " + to_string(this->left_cash[3]) + "장 출금가능" << endl;
			cout << "======================================" << endl;
			cout << "1,000원 장수를 입력해주세요:";
			cin >> won_1;
			cout << "5,000원 장수를 입력해주세요:";
			cin >> won_5;
			cout << "10,000원 장수를 입력해주세요:";
			cin >> won_10;
			cout << "50,000원 장수를 입력해주세요:";
			cin >> won_50;
			if ((won_1 > this->left_cash[0]) || (won_5 > this->left_cash[1]) || (won_10 > this->left_cash[2]) || (won_50 > this->left_cash[3])) {
				cout << "======================================" << endl;
				cout << "오류 : 요청하신 만큼의 지폐를 보유하고 있지 않습니다" << endl;
				cout << "======================================" << endl;
				button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
				continue;
			}
			amount = won_1 * 1000 + won_5 * 5000 + won_10 * 10000 + won_50 * 50000;
			if (total_amount != amount) {
				cout << "======================================" << endl;
				cout << "오류 : 출금을 원하시는 금액과 일치하지 않습니다" << endl;
				cout << "======================================" << endl;
				button = total_amount = amount = won_1 = won_5 = won_10 = won_50 = 0;
				continue;
			}
			cout << "======================================" << endl;
			cout << "수수료가 " + to_string(this->fee_withdrawal_primary) + "원 발생했습니다" << endl;
			cout << "======================================" << endl;
			if (total_amount + this->fee_withdrawal_primary > a->account_Balance()) {
				cout << "======================================" << endl;
				cout << "오류 : 출금 금액과 수수료의 합보다 계좌잔액이 부족합니다" << endl;
				cout << "======================================" << endl;
				button = total_amount = amount = won_1 = won_5 = won_10 = won_50 = 0;
				continue;
			}
			a->account_Withdrawl(total_amount + this->fee_withdrawal_primary);
			this->left_cash[0] -= won_1;
			this->left_cash[1] -= won_5;
			this->left_cash[2] -= won_10;
			this->left_cash[3] -= won_50;
			return total_amount;
		}
		else if (button == 2) {
			cout << "======================================" << endl;
			cout << "출금 나가기" << endl;
			cout << "======================================" << endl;
			return -1;
		}
		else {
			cout << "======================================" << endl;
			cout << "오류 : 잘못된 입력입니다" << endl;
			cout << "메뉴를 다시 입력해주세요" << endl;
			cout << "======================================" << endl;
			continue;
		}
	}
}

int Atm_SingleBank::Transfer_Kor(Account* a1, Account* a2) {
	int button{ 0 }; // 메뉴 선택 버튼
	int verify_button{ 0 }; // 현금 송금 확인 버튼
	// 현금 입력 시 지폐 별 개수 저장, 수표 개수 저장
	int won_1{ 0 }, won_5{ 0 }, won_10{ 0 }, won_50{ 0 };
	int total_amount{ 0 }; // 총 투입 금액
	// 예외 발생 시 처음 Deposit 상태로 돌아오기 위해 무한 루프로 구현
	while (1) {
		// Transfer을 시작할지 안할지 선택
		cout << "======================================" << endl;
		cout << "송금 유형을 선택하세요" << endl;
		cout << "번호를 입력하세요" << endl;
		cout << "=======================================================" << endl;
		cout << "|  1. 현금 이체 |  2. 계좌 이체  |  3. 나가기  |" << endl;
		cout << "=======================================================" << endl;
		cin >> button;
		// Cash 선택 시
		if (button == 1) {
			cout << "======================================" << endl;
			cout << "입금하고자 하는 현금의 지폐수를 입력해주세요" << endl;
			cout << "한 번에 최대 " + to_string(this->getable_cash_num) + " 장까지 처리 가능합니다" << endl;
			cout << "======================================" << endl;
			cout << "1,000원 장수를 입력하세요 :";
			cin >> won_1;
			cout << "5,000원 장수를 입력하세요 :";
			cin >> won_5;
			cout << "10,000원 장수를 입력하세요 :";
			cin >> won_10;
			cout << "50,000원 장수를 입력하세요 :";
			cin >> won_50;
			// ATM이 수용 가능한 지폐 개수 초과시 에러 메세지 출력 및 Deposit 재실행
			if (won_1 + won_5 + won_10 + won_50 > this->getable_cash_num) {
				button = won_1 = won_5 = won_10 = won_50 = 0;
				cout << "======================================" << endl;
				cout << "오류 : ATM이 한 번에 처리할 수 있는 지폐의 장수를 초과하였습니다" << endl;
				cout << "======================================" << endl;
				continue;
			}
			// ATM 지폐 개수 및 Account 잔액 update
			total_amount = 1000 * won_1 + 5000 * won_5 + 10000 * won_10 + 50000 * won_50;
			cout << to_string(total_amount) + "원을 송금하시겠습니까?" << endl;
			cout << "========================" << endl;
			cout << "|  1. 네  |  2. 아니오  |" << endl;
			cout << "========================" << endl;
			cin >> verify_button;
			if (verify_button != 1) {
				verify_button = button = won_1 = won_5 = won_10 = won_50 = 0;
				cout << "처음 메뉴로 돌아갑니다" << endl;
				continue;
			}
			// a2 은행이 primary bank인 경우
			if (this->primary_bank->bank_Name() == a2->account_Bank()) {
				cout << "======================================" << endl;
				cout << "수수료가 " + to_string(this->fee_transfer_primary_primary) + "원 발생했습니다" << endl;
				cout << "======================================" << endl;
				// ATM에 투입한 금액이 수수료보다 작을 때
				if (total_amount < this->fee_transfer_primary_primary) {
					cout << "======================================" << endl;
					cout << "오류 : 송금 금액이 수수료보다 작습니다" << endl;
					cout << "======================================" << endl;
					button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
					continue;
				}
				a2->account_Deposit(total_amount - this->fee_transfer_primary_primary);
				this->left_cash[0] += won_1;
				this->left_cash[1] += won_5;
				this->left_cash[2] += won_10;
				this->left_cash[3] += won_50;
				return total_amount - this->fee_transfer_primary_primary;
			}
			// a2 은행이 another bank인 경우
			else {
				cout << "======================================" << endl;
				cout << "수수료가 " + to_string(this->fee_transfer_primary_non_primary) + "원 발생했습니다" << endl;
				cout << "======================================" << endl;
				// ATM에 투입한 금액이 수수료보다 작을 때
				if (total_amount < this->fee_transfer_primary_non_primary) {
					cout << "======================================" << endl;
					cout << "오류 : 송금 금액이 수수료보다 작습니다" << endl;
					cout << "======================================" << endl;
					button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
					continue;
				}
				a2->account_Deposit(total_amount - this->fee_transfer_primary_non_primary);
				this->left_cash[0] += won_1;
				this->left_cash[1] += won_5;
				this->left_cash[2] += won_10;
				this->left_cash[3] += won_50;
				return total_amount - this->fee_transfer_primary_non_primary;
			}
		}
		// Bank 선택 시
		else if (button == 2) {
			cout << "======================================" << endl;
			cout << "송금 금액을 입력하세요" << endl;
			cout << "======================================" << endl;
			cout << "송금 금액 : ";
			cin >> total_amount;
			// a2 은행이 primary bank인 경우
			if (this->primary_bank->bank_Name() == a2->account_Bank()) {
				cout << "======================================" << endl;
				cout << "수수료가 " + to_string(this->fee_transfer_primary_primary) + "원 발생했습니다" << endl;
				cout << "======================================" << endl;
				// 송금 금액과 수수료 합이 계좌 잔액보다 클때
				if (total_amount + this->fee_transfer_primary_primary > a1->account_Balance()) {
					cout << "======================================" << endl;
					cout << "오류 : 계좌 잔액이 송금 금액과 수수료의 합보다 작습니다" << endl;
					cout << "======================================" << endl;
					button = total_amount = 0;
					continue;
				}
				a1->account_Withdrawl(total_amount + this->fee_transfer_primary_primary);
				a2->account_Deposit(total_amount);
				return total_amount;
			}
			// a2 은행이 another bank인 경우
			else {
				cout << "======================================" << endl;
				cout << "수수료가 " + to_string(this->fee_transfer_primary_non_primary) + "원 발생했습니다" << endl;
				cout << "======================================" << endl;
				// 송금 금액과 수수료 합이 계좌 잔액보다 클때
				if (total_amount + this->fee_transfer_primary_non_primary > a1->account_Balance()) {
					cout << "======================================" << endl;
					cout << "오류 : 계좌 잔액이 송금 금액과 수수료의 합보다 작습니다" << endl;
					cout << "======================================" << endl;
					button = total_amount = 0;
					continue;
				}
				a1->account_Withdrawl(total_amount + this->fee_transfer_primary_non_primary);
				a2->account_Deposit(total_amount);
				return total_amount;
			}
		}
		// Exit 선택 시 
		else if (button == 3) {
			cout << "======================================" << endl;
			cout << "송금 나가기" << endl;
			cout << "======================================" << endl;
			return -1;
		}
		// 그 외 다른 button이 눌렸을 시 에러 메시지 출력 및 Deposit 재실행
		else {
			cout << "======================================" << endl;
			cout << "오류 : 잘못된 입력" << endl;
			cout << "송금 유형을 다시 선택하세요" << endl;
			cout << "======================================" << endl;
			continue;
		}
	}
}

bool Atm_SingleBank::user_Authorize_Kor(Account* a) {
	int pw{ 0 };
	int wrong_count{ 3 };
	while (1) {
		cout << "======================================" << endl;
		cout << "비밀번호를 입력하세요 :";
		cin >> pw;
		cout << "======================================" << endl;
		if (pw != a->account_Password()) {
			pw = 0;
			wrong_count -= 1;
			cout << "======================================" << endl;
			cout << "오류 : 비밀번호를 잘못 입력하셨습니다" << endl;
			cout << "======================================" << endl;
			if (wrong_count == 0) {
				cout << "======================================" << endl;
				cout << "더 이상 비밀번호를 입력하실 수 없습니다" << endl;
				cout << "======================================" << endl;
				return false;
			}
			cout << "======================================" << endl;
			cout << to_string(wrong_count) + "번의 기회가 남았습니다" << endl;
			cout << "======================================" << endl;
			continue;
		}
		return true;
	}
}

// session에서 발생할 수 있는 예외사항들을 케이스별로 분류해 넣어놓음
class Session_exception { };
class Num_exception : public Session_exception { }; // 숫자범위를 벗어났을 시 
class Cin_exception : public Session_exception { }; // 숫자를 입력해야 하는데 문자를 입력했을 시
class Primary_exception : public Session_exception { }; // SingleBank에 다른 은행 카드를 입력했을 시
class Invalid_account : public Session_exception { }; // Session에 유효하지 않은 Card가 들어왔을 시
class Invalid_password : public Session_exception { }; // 유효하지 않은 비밀번호를 입력시
class Invalid_account_num : public Session_exception { }; // 유효하지 않은 계좌 자리수
class File_open_fail : public Session_exception { }; // 파일열기가 실패할 시

void Atm_SingleBank::session_Start(Card* c) {
	if (is_ul == true) {
		if (c->is_Admin() == true) {
			session_Admin(c);
		}
		else {
			session_Main(c);
		}
	}
	else {
		// 무슨 세션을 선택할 건지 정하는 부분
		int session_indicator = 0;
		while (true) {
			int select_num = 1;
			std::cout << "======================================" << endl;
			std::cout << "Which language do you want to use?" << endl;
			std::cout << "1 : English / 2 : Korean" << endl;
			std::cout << "======================================" << endl;
			cin >> select_num;
			try {
				// cin에서 잘못된 자료형을 받으면 cin.fail()이 true가 된다. 이때 예외처리하면 됨. >> 잘못된 자료형의 경우는 이렇게 처리하면 될 듯.
				if (cin.fail()) {
					throw Cin_exception();
				}
				if (select_num == 1) {
					session_indicator = 1;
					break;
				}
				else if (select_num == 2) {
					session_indicator = 2;
					break;
				}
				// 잘못된 숫자가 들어올 경우 예외처리
				else {
					throw Num_exception();
				}
			}
			catch (Num_exception) {
				std::cout << "======================================" << endl;
				std::cout << "Input only number 1 or 2" << endl;
				std::cout << "======================================" << endl;
			}
			// 잘못된 자료형을 입력했을 때 예외처리
			catch (Cin_exception) {
				// cin에 잘못된 자료형이 들어가면 cin의 버퍼를 지워줘야 다음 while문에서 cin를 사용시 infinite loop가 발생하지 않는다.
				std::cout << "======================================" << endl;
				std::cout << "Input only number 1 or 2. Not Charactor." << endl;
				std::cout << "======================================" << endl;
				// cin의 버퍼를 지워주는 부분
				cin.clear();
				cin.ignore(256, '\n');
			}
		}
		// 영어 세션을 불러온다
		if (session_indicator == 1) {
			if (c->is_Admin() == true) {
				session_Admin(c);
			}
			else {
				session_Main(c);
			}
		}
		// 한글 세션을 불러온다
		else {
			if (c->is_Admin() == true) {
				session_Admin_Kor(c);
			}
			else {
				session_Main_Kor(c);
			}
		}
	}
}

void Atm_SingleBank::session_Main(Card* c) {
	std::cout << "======================================" << endl;
	std::cout << "Welcome to " + primary_bank->bank_Name() + " ATM" << endl;
	std::cout << "======================================" << endl;
	// session에서 이루어지는 모든 거래를 추적해서 기록하는 string을 하나 만든다.
	string session_transac_history = "Session : " + to_string(called_session_num) + "\n";
	string session_transac_history_kor = "세션 : " + to_string(called_session_num) + "\n";
	// account transaction에 더할 거래기록 저장공간
	string session_transac_accountSave = "Transactin history in " + primary_bank->bank_Name() + " ATM " + to_string(atm_serial) + "\n";
	string session_transac_accountSave_kor = primary_bank->bank_Name() + " ATM " + to_string(atm_serial) + " 에서 일어난 거래기록\n";
	// 들어온 카드의 Account pointer를 담는 곳
	Account* card_account = nullptr;
	// 출금 횟수를 세는 indicator
	int withdrawal_indicator = 0;
	try {
		// 우선 들어온 카드가 primary bank인지 확인해야 한다. SingleBank의 경우 primary bank가 아니면 session을 종료한다.
		if (c->bank_Name() != primary_bank->bank_Name()) {
			throw Primary_exception();
		}

		// 들어온 카드의 Account pointer를 파악해서 card_account에 넣어야 한다. 만약 없는 Account면 그대로 session을 종료한다.
		Account* temp_account = primary_bank->search_myAccount(c->account_Num());
		if (temp_account == primary_bank->ret_zeroAccount()) {
			throw Invalid_account();
		}
		else {
			card_account = temp_account;
		}

		session_transac_history += card_account->account_Num() + "'s transaction history\n";
		session_transac_history_kor += card_account->account_Num() + "의 거래기록\n";

		card_account->transaction_Add(session_transac_accountSave, session_transac_accountSave_kor);

		// 계좌의 비밀번호를 물어본다. 이때 true면 계속 진행하고 false면 예외처리
		bool temp_pw_valid = user_Authorize(card_account);
		if (temp_pw_valid == false) {
			throw Invalid_password();
		}

		// 드디어 실제로 거래를 처리하는 세션까지 왔다.
		do {
			int select_num = 0;
			std::cout << "======================================" << endl;
			std::cout << "Select the option you want to choose" << endl;
			std::cout << "1 : Deposit" << endl;
			std::cout << "2 : Withdrawal" << endl;
			std::cout << "3 : Transfer" << endl;
			std::cout << "4 : Transaction History" << endl;
			std::cout << "5 : Exit" << endl;
			std::cout << "======================================" << endl;
			cin >> select_num;
			try {
				// 잘못된 값이 들어오면 Cin_exception을 던진다. 
				if (cin.fail()) {
					throw Cin_exception();
				}
				if (select_num == 1) {
					int deal_money = Deposit(card_account);
					if (deal_money > 0) {
						// 거래가 끝난 후 거래 내역을 저장하는 곳
						string deposit_history = to_string(deal_money) + "Won added to " + card_account->account_Num() + "\n";
						string deposit_history_kor = to_string(deal_money) + "원이 " + card_account->account_Num() + "에 입금되었습니다." + "\n";
						session_transac_history += deposit_history;
						session_transac_history_kor += deposit_history_kor;
						card_account->transaction_Add(deposit_history, deposit_history_kor);
					}
					else if (deal_money == -1) {
						continue;
					}
				}
				else if (select_num == 2) {
					if (withdrawal_indicator > max_withdrawal) {
						std::cout << "======================================" << endl;
						std::cout << "Your available withdrawal chance is gone." << endl;
						std::cout << "======================================" << endl;
					}
					else {
						int deal_money = Withdrawal(card_account);
						if (deal_money > 0) {
							withdrawal_indicator += 1;
							// 거래가 끝난 후 거래 내역을 저장하는 곳
							string withdrawal_history = to_string(deal_money) + "Won withdrawed from " + card_account->account_Num() + "\n";
							string withdrawal_history_kor = to_string(deal_money) + "원이 " + card_account->account_Num() + "에서 출금되었습니다." + "\n";
							session_transac_history += withdrawal_history;
							session_transac_history_kor += withdrawal_history_kor;
							card_account->transaction_Add(withdrawal_history, withdrawal_history_kor);
						}
						else if (deal_money == -1) {
							continue;
						}
					}
				}
				else if (select_num == 3) {
					// 보낼 계좌번호를 받는 부분
					string temp_sending_account = "";
					Account* temp_sending_accountptr = nullptr;
					do {
						std::cout << "======================================" << endl;
						std::cout << "Which account do you want to send?" << endl;
						std::cout << "======================================" << endl;
						cin >> temp_sending_account;
						try {
							// 계좌번호 자릿수가 맞지 않으면 다시 while문을 돌려야 한다.  
							if (temp_sending_account.length() != 14) {
								throw Invalid_account_num();
							}
							// 계좌번호의 pointer를 찾는다. 존재하지 않는다면 다시 while문을 돌려야 한다.
							temp_sending_accountptr = primary_bank->search_myAccount(temp_sending_account);
							if (temp_sending_accountptr == primary_bank->ret_zeroAccount()) {
								temp_sending_accountptr = primary_bank->search_anotherAccount(temp_sending_account);
								if (temp_sending_accountptr == primary_bank->ret_zeroAccount()) {
									throw Invalid_account();
								}
								else {
									// 실제로 다른 은행에 계좌번호가 존재하는 경우 : break
									break;
								}
							}
							else {
								// 실제로 자기 은행에 계좌번호가 존재하는 경우 : break
								break;
							}
						}
						catch (Invalid_account_num) {
							std::cout << "======================================" << endl;
							std::cout << "Account number is not match" << endl;
							std::cout << "======================================" << endl;
						}
						catch (Invalid_account) {
							std::cout << "======================================" << endl;
							std::cout << "Account is not exist" << endl;
							std::cout << "======================================" << endl;
						}
					} while (true);
					// 받은 계좌번호 포인터를 Transfer함수에 집어넣기
					int deal_money = Transfer(card_account, temp_sending_accountptr);
					if (deal_money > 0) {
						// 거래 내역을 기록한다.
						string transfer_history = to_string(deal_money) + "Won transfered from " + card_account->account_Num() + " to " + temp_sending_accountptr->account_Num() + "\n";
						string transfer_history_kor = to_string(deal_money) + "원이 " + card_account->account_Num() + " 에서 " + temp_sending_accountptr->account_Num() + "으로 송금되었습니다." + "\n";
						string transfer_history_account2 = "transfer from another account : " + transfer_history;
						string transfer_history_account2_kor = "다른 계좌에서 온 송금 : " + transfer_history_kor;
						session_transac_history += transfer_history;
						session_transac_history_kor += transfer_history_kor;
						card_account->transaction_Add(transfer_history, transfer_history_kor);
						temp_sending_accountptr->transaction_Add(transfer_history_account2, transfer_history_account2_kor);
					}
					else if (deal_money == -1) {
						continue;
					}
				}
				else if (select_num == 4) {
					std::cout << "======================================" << endl;
					std::cout << "Account's Bank : " + card_account->account_Bank() << endl;
					std::cout << "Account's User : " + card_account->account_User() << endl;
					std::cout << "Account Number : " + card_account->account_Num() << endl;
					std::cout << "Account Balance : " + to_string(card_account->account_Balance()) << endl;
					std::cout << "Your account transaction history is : \n";
					std::cout << card_account->ret_transac_history(true) << endl;
					std::cout << "======================================" << endl;
				}
				else if (select_num == 5) {
					break;
				}
				else {
					throw Num_exception();
				}
			}
			catch (Cin_exception) {
				// cin에 잘못된 자료형이 들어가면 cin의 버퍼를 지워줘야 다음 while문에서 cin를 사용시 infinite loop가 발생하지 않는다.
				std::cout << "======================================" << endl;
				std::cout << "Input only number 1, 2, 3 or 4. Not Charactor." << endl;
				std::cout << "======================================" << endl;
				// cin의 버퍼를 지워주는 부분
				cin.clear();
				cin.ignore(256, '\n');
			}
			catch (Num_exception) {
				std::cout << "======================================" << endl;
				std::cout << "Input only number 1, 2, 3, 4 or 5" << endl;
				std::cout << "======================================" << endl;
			}
		} while (true);

		// 그 모든 과정을 거치고서도 거래가 성공적으로 완료되었다는 뜻이니 Session을 종료한다. 
		write_Transac_history(session_transac_history, session_transac_history_kor);
		std::cout << "======================================" << endl;
		std::cout << "Account Balance : " + to_string(card_account->account_Balance()) << endl;
		std::cout << "total transaction in this ATM session : \n" + session_transac_history;
		std::cout << "Closing ATM Session." << endl;
		std::cout << "======================================" << endl;
		called_session_num += 1;
	}
	// Card에 있는 account가 없는 account일시 
	catch (Invalid_account) {
		// session_transac_history에 기록할 메시지 작성해서 기록
		session_transac_history += "Session Terminated : Account does not exist\n";
		session_transac_history_kor += "세션 종료 : 존재하지 않는 계좌\n";
		// Session이 종료되었으니 Atm의 transac_history에 session_transac_history를 기록
		write_Transac_history(session_transac_history, session_transac_history_kor);
		// 에러 메시지 출력
		std::cout << "======================================" << endl;
		std::cout << "Account does not exist." << endl;
		// 세션이 종료되니 session_transac_history를 출력
		std::cout << "total transaction in this ATM session : \n" + session_transac_history;
		std::cout << "Closing ATM Session." << endl;
		std::cout << "======================================" << endl;
		called_session_num += 1;
	}
	// primary bank가 아닌 Card가 들어왔을 시
	catch (Primary_exception) {
		// session_transac_history에 기록할 메시지 작성해서 기록
		session_transac_history += "Session Terminated : Account's bank is not primary bank\n";
		session_transac_history_kor += "세션 종료 : 계좌의 은행이 primary bank가 아님\n";
		// Session이 종료되었으니 Atm의 transac_history에 session_transac_history를 기록
		write_Transac_history(session_transac_history, session_transac_history_kor);
		// 에러 메시지 출력
		std::cout << "======================================" << endl;
		std::cout << "We only accept " + primary_bank->bank_Name() + "account." << endl;
		// 세션이 종료되니 session_transac_history를 출력
		std::cout << "total transaction in this ATM session : \n" + session_transac_history;
		std::cout << "Closing ATM Session." << endl;
		std::cout << "======================================" << endl;
		called_session_num += 1;
	}
	// password가 틀렸을 시
	catch (Invalid_password) {
		// session_transac_history에 기록할 메시지 작성해서 기록
		session_transac_history += "Session Terminated : Invalid Password\n";
		session_transac_history_kor += "세션 종료 : 비밀번호 다름\n";
		// Session이 종료되었으니 Atm의 transac_history에 session_transac_history를 기록
		write_Transac_history(session_transac_history, session_transac_history_kor);
		card_account->transaction_Add("Session Terminated : Invalid Password\n", "세션 종료 : 비밀번호 다름\n");
		// 에러 메시지 출력
		std::cout << "======================================" << endl;
		std::cout << "Invalid Password" << endl;
		// 세션이 종료되니 session_transac_history를 출력
		std::cout << "total transaction in this ATM session : \n" + session_transac_history;
		std::cout << "Closing ATM Session." << endl;
		std::cout << "======================================" << endl;
		called_session_num += 1;
	}
}

void Atm_SingleBank::session_Main_Kor(Card* c) {
	std::cout << "======================================" << endl;
	std::cout << primary_bank->bank_Name() + " ATM 이용을 환영합니다." << endl;
	std::cout << "======================================" << endl;
	// session에서 이루어지는 모든 거래를 추적해서 기록하는 string을 하나 만든다.
	string session_transac_history = "Session : " + to_string(called_session_num) + "\n";
	string session_transac_history_kor = "세션 : " + to_string(called_session_num) + "\n";
	// account transaction에 더할 거래기록 저장공간
	string session_transac_accountSave = ">> Transactin history in " + primary_bank->bank_Name() + " ATM " + to_string(atm_serial) + "\n";
	string session_transac_accountSave_kor = primary_bank->bank_Name() + " ATM " + to_string(atm_serial) + " 에서 일어난 거래기록\n";
	// 들어온 카드의 Account pointer를 담는 곳
	Account* card_account = nullptr;
	// 출금한 횟수를 저장하는 곳
	int withdrawal_indicator = 0;
	try {
		// 우선 들어온 카드가 primary bank인지 확인해야 한다. SingleBank의 경우 primary bank가 아니면 session을 종료한다.
		if (c->bank_Name() != primary_bank->bank_Name()) {
			throw Primary_exception();
		}

		// 들어온 카드의 Account pointer를 파악해서 card_account에 넣어야 한다. 만약 없는 Account면 그대로 session을 종료한다.
		Account* temp_account = primary_bank->search_myAccount(c->account_Num());
		if (temp_account == primary_bank->ret_zeroAccount()) {
			throw Invalid_account();
		}
		else {
			card_account = temp_account;
		}

		session_transac_history += card_account->account_Num() + "'s transaction history\n";
		session_transac_history_kor += card_account->account_Num() + "의 거래기록\n";

		card_account->transaction_Add(session_transac_accountSave, session_transac_accountSave_kor);

		// 계좌의 비밀번호를 물어본다. 이때 true면 계속 진행하고 false면 예외처리
		bool temp_pw_valid = user_Authorize_Kor(card_account);
		if (temp_pw_valid == false) {
			throw Invalid_password();
		}

		// 드디어 실제로 거래를 처리하는 세션까지 왔다.
		do {
			int select_num = 0;
			std::cout << "======================================" << endl;
			std::cout << "원하는 거래를 선택하세요" << endl;
			std::cout << "1 : 입금" << endl;
			std::cout << "2 : 출금" << endl;
			std::cout << "3 : 송금" << endl;
			std::cout << "4 : 거래 기록" << endl;
			std::cout << "5 : 종료" << endl;
			std::cout << "======================================" << endl;
			cin >> select_num;
			try {
				// 잘못된 값이 들어오면 Cin_exception을 던진다. 
				if (cin.fail()) {
					throw Cin_exception();
				}
				if (select_num == 1) {
					int deal_money = Deposit_Kor(card_account);
					if (deal_money > 0) {
						// 거래가 끝난 후 거래 내역을 저장하는 곳
						string deposit_history = to_string(deal_money) + "Won added to " + card_account->account_Num() + "\n";
						string deposit_history_kor = to_string(deal_money) + "원이 " + card_account->account_Num() + "에 입금되었습니다." + "\n";
						session_transac_history += deposit_history;
						session_transac_history_kor += deposit_history_kor;
						card_account->transaction_Add(deposit_history, deposit_history_kor);
					}
					else if (deal_money == -1) {
						continue;
					}
				}
				else if (select_num == 2) {
					if (withdrawal_indicator > max_withdrawal) {
						std::cout << "======================================" << endl;
						std::cout << "세션당 출금할 수 있는 횟수를 초과했습니다." << endl;
						std::cout << "======================================" << endl;
					}
					else {
						int deal_money = Withdrawal_Kor(card_account);
						if (deal_money > 0) {
							withdrawal_indicator += 1;
							// 거래가 끝난 후 거래 내역을 저장하는 곳
							string withdrawal_history = to_string(deal_money) + "Won withdrawed from " + card_account->account_Num() + "\n";
							string withdrawal_history_kor = to_string(deal_money) + "원이 " + card_account->account_Num() + "에서 출금되었습니다." + "\n";
							session_transac_history += withdrawal_history;
							session_transac_history_kor += withdrawal_history_kor;
							card_account->transaction_Add(withdrawal_history, withdrawal_history_kor);
						}
						else if (deal_money == -1) {
							continue;
						}
					}
				}
				else if (select_num == 3) {
					// 보낼 계좌번호를 받는 부분
					string temp_sending_account = "";
					Account* temp_sending_accountptr = nullptr;
					do {
						std::cout << "======================================" << endl;
						std::cout << "송금할 계좌의 계좌번호를 입력하세요." << endl;
						std::cout << "======================================" << endl;
						cin >> temp_sending_account;
						try {
							// 계좌번호 자릿수가 맞지 않으면 다시 while문을 돌려야 한다.  
							if (temp_sending_account.length() != 14) {
								throw Invalid_account_num();
							}
							// 계좌번호의 pointer를 찾는다. 존재하지 않는다면 다시 while문을 돌려야 한다.
							temp_sending_accountptr = primary_bank->search_myAccount(temp_sending_account);
							if (temp_sending_accountptr == primary_bank->ret_zeroAccount()) {
								temp_sending_accountptr = primary_bank->search_anotherAccount(temp_sending_account);
								if (temp_sending_accountptr == primary_bank->ret_zeroAccount()) {
									throw Invalid_account();
								}
								else {
									// 실제로 다른 은행에 계좌번호가 존재하는 경우 : break
									break;
								}
							}
							else {
								// 실제로 자기 은행에 계좌번호가 존재하는 경우 : break
								break;
							}
						}
						catch (Invalid_account_num) {
							std::cout << "======================================" << endl;
							std::cout << "계좌번호 길이가 맞지 않습니다." << endl;
							std::cout << "======================================" << endl;
						}
						catch (Invalid_account) {
							std::cout << "======================================" << endl;
							std::cout << "계좌번호가 존재하지 않습니다." << endl;
							std::cout << "======================================" << endl;
						}
					} while (true);
					// 받은 계좌번호 포인터를 Transfer함수에 집어넣기
					int deal_money = Transfer_Kor(card_account, temp_sending_accountptr);
					if (deal_money > 0) {
						// 거래 내역을 기록한다.
						string transfer_history = to_string(deal_money) + "Won transfered from " + card_account->account_Num() + " to " + temp_sending_accountptr->account_Num() + "\n";
						string transfer_history_kor = to_string(deal_money) + "원이 " + card_account->account_Num() + " 에서 " + temp_sending_accountptr->account_Num() + "으로 송금되었습니다." + "\n";
						string transfer_history_account2 = "transfer from another account : " + transfer_history;
						string transfer_history_account2_kor = "다른 계좌에서 온 송금 : " + transfer_history_kor;
						session_transac_history += transfer_history;
						session_transac_history_kor += transfer_history_kor;
						card_account->transaction_Add(transfer_history, transfer_history_kor);
						temp_sending_accountptr->transaction_Add(transfer_history_account2, transfer_history_account2_kor);
					}
					else if (deal_money == -1) {
						continue;
					}
				}
				else if (select_num == 4) {
					std::cout << "======================================" << endl;
					std::cout << "계좌 은행 : " + card_account->account_Bank() << endl;
					std::cout << "계좌 주인 : " + card_account->account_User() << endl;
					std::cout << "계좌 번호 : " + card_account->account_Num() << endl;
					std::cout << "계좌 잔액 : " + to_string(card_account->account_Balance()) << endl;
					std::cout << "계좌 거래 기록은 다음과 같습니다. : " << endl;
					std::cout << card_account->ret_transac_history(false);
					std::cout << "======================================" << endl;
				}
				else if (select_num == 5) {
					break;
				}
				else {
					throw Num_exception();
				}
			}
			catch (Cin_exception) {
				// cin에 잘못된 자료형이 들어가면 cin의 버퍼를 지워줘야 다음 while문에서 cin를 사용시 infinite loop가 발생하지 않는다.
				std::cout << "======================================" << endl;
				std::cout << "문자가 아닌 숫자 1,2,3,4, 5 중 하나를 입력하세요." << endl;
				std::cout << "======================================" << endl;
				// cin의 버퍼를 지워주는 부분
				cin.clear();
				cin.ignore(256, '\n');
			}
			catch (Num_exception) {
				std::cout << "======================================" << endl;
				std::cout << "숫자 1, 2, 3, 4, 5 중 하나를 입력하세요" << endl;
				std::cout << "======================================" << endl;
			}
		} while (true);

		// 그 모든 과정을 거치고서도 거래가 성공적으로 완료되었다는 뜻이니 Session을 종료한다. 
		write_Transac_history(session_transac_history, session_transac_history_kor);
		std::cout << "======================================" << endl;
		std::cout << "계좌 잔액 : " + to_string(card_account->account_Balance()) << endl;
		std::cout << "이번 ATM 세션에서 일어난 거래는 다음과 같습니다. : \n" + session_transac_history_kor;
		std::cout << "ATM 세션을 종료합니다." << endl;
		std::cout << "======================================" << endl;
		called_session_num += 1;
	}
	// Card에 있는 account가 없는 account일시 
	catch (Invalid_account) {
		// session_transac_history에 기록할 메시지 작성해서 기록
		session_transac_history += "Session Terminated : Account does not exist\n";
		session_transac_history_kor += "세션 종료 : 존재하지 않는 계좌\n";
		// Session이 종료되었으니 Atm의 transac_history에 session_transac_history를 기록
		write_Transac_history(session_transac_history, session_transac_history_kor);
		// 에러 메시지 출력
		std::cout << "======================================" << endl;
		std::cout << "유효하지 않은 카드입니다." << endl;
		// 세션이 종료되니 session_transac_history를 출력
		std::cout << "이번 ATM 세션에서 일어난 거래는 다음과 같습니다. : \n" + session_transac_history_kor;
		std::cout << "ATM 세션을 종료합니다." << endl;
		std::cout << "======================================" << endl;
		called_session_num += 1;
	}
	// primary bank가 아닌 Card가 들어왔을 시
	catch (Primary_exception) {
		// session_transac_history에 기록할 메시지 작성해서 기록
		session_transac_history += "Session Terminated : Account's bank is not primary bank\n";
		session_transac_history_kor += "세션 종료 : 계좌의 은행이 primary bank가 아님\n";
		// Session이 종료되었으니 Atm의 transac_history에 session_transac_history를 기록
		write_Transac_history(session_transac_history, session_transac_history_kor);
		// 에러 메시지 출력
		std::cout << "======================================" << endl;
		std::cout << "이 ATM은 오로지 " + primary_bank->bank_Name() + " 계좌만 취급합니다." << endl;
		// 세션이 종료되니 session_transac_history를 출력
		std::cout << "이번 ATM 세션에서 일어난 거래는 다음과 같습니다. : \n" + session_transac_history_kor;
		std::cout << "ATM 세션을 종료합니다." << endl;
		std::cout << "======================================" << endl;
		called_session_num += 1;
	}
	// password가 틀렸을 시
	catch (Invalid_password) {
		// session_transac_history에 기록할 메시지 작성해서 기록
		session_transac_history += "Session Terminated : Invalid Password\n";
		session_transac_history_kor += "Session Terminated : Invalid Password\n";
		// Session이 종료되었으니 Atm의 transac_history에 session_transac_history를 기록
		write_Transac_history(session_transac_history, session_transac_history_kor);
		card_account->transaction_Add("Session Terminated : Invalid Password\n", "Session Terminated : Invalid Password\n");
		// 에러 메시지 출력
		std::cout << "======================================" << endl;
		std::cout << "유효하지 않은 비밀번호입니다." << endl;
		// 세션이 종료되니 session_transac_history를 출력
		std::cout << "이번 ATM 세션에서 일어난 거래는 다음과 같습니다. : \n" + session_transac_history_kor;
		std::cout << "ATM 세션을 종료합니다." << endl;
		std::cout << "======================================" << endl;
		called_session_num += 1;
	}
}

void Atm_SingleBank::session_Admin(Card* c) {
	std::cout << "======================================" << endl;
	std::cout << "Welcome to " + primary_bank->bank_Name() + " ATM Admin Session." << endl;
	std::cout << "======================================" << endl;
	string session_transac_history = "Admin Session : " + to_string(called_session_num) + "\n";
	string session_transac_history_kor = "관리자 세션 : " + to_string(called_session_num) + "\n";
	// 바로 메뉴 하나를 보여준다. 
	try {
		if (c->bank_Name() != primary_bank->bank_Name()) {
			throw Primary_exception();
		}
		do {
			int select_num = 0;
			std::cout << "======================================" << endl;
			std::cout << primary_bank->bank_Name() + " ATM " + to_string(atm_serial) + " Admin Menu" << endl;
			std::cout << "Select the option you want to choose." << endl;
			std::cout << "1. Transaction History" << endl;
			std::cout << "2. Exit" << endl;
			std::cout << "======================================" << endl;
			cin >> select_num;
			try {
				if (cin.fail()) {
					throw Cin_exception();
				}
				if (select_num == 1) {
					// 거래기록 파일 내보내기
					ofstream fout;
					string output_filename = primary_bank->bank_Name() + " ATM " + to_string(atm_serial) + " transac_history_eng.txt";
					fout.open(output_filename);
					try {
						if (!fout) {
							throw File_open_fail();
						}
						fout << primary_bank->bank_Name() + " ATM " + to_string(atm_serial) + " transac_history\n";
						fout << transac_history;
						std::cout << "======================================" << endl;
						std::cout << "Transaction history output successed." << endl;
						std::cout << "======================================" << endl;
						fout.close();
					}
					catch (File_open_fail) {
						std::cout << "======================================" << endl;
						std::cout << "Transaction history output failed." << endl;
						std::cout << "======================================" << endl;
						fout.close();
					}
					std::cout << "======================================" << endl;
					std::cout << "Total called session : " + to_string(called_session_num) << endl;
					std::cout << "Transaction history of ATM : " << endl;
					std::cout << "======================================" << endl;
					std::cout << transac_history << endl;
					session_transac_history += "ATM transaction history viewed\n";
					session_transac_history_kor += "ATM 거래기록 조회됨\n";
				}
				else if (select_num == 2) {
					break;
				}
				else {
					throw Num_exception();
				}
			}
			catch (Cin_exception) {
				// cin에 잘못된 자료형이 들어가면 cin의 버퍼를 지워줘야 다음 while문에서 cin를 사용시 infinite loop가 발생하지 않는다.
				std::cout << "======================================" << endl;
				std::cout << "Input only number 1 or 2. Not Charactor." << endl;
				std::cout << "======================================" << endl;
				// cin의 버퍼를 지워주는 부분
				cin.clear();
				cin.ignore(256, '\n');
			}
			catch (Num_exception) {
				std::cout << "======================================" << endl;
				std::cout << "Input only number 1 or 2." << endl;
				std::cout << "======================================" << endl;
			}
		} while (true);
	}
	catch (Primary_exception) {
		std::cout << "======================================" << endl;
		std::cout << "Invalid Admin Card" << endl;
		std::cout << "======================================" << endl;
		session_transac_history += "Admin Session terminated : Invalid Admin Card used.\n";
		session_transac_history_kor += "관리자 세션 종료 : 유효하지 않은 관리자 카드가 사용되었습니다.\n";
	}
	// 세션이 종료됨.
	std::cout << "======================================" << endl;
	std::cout << "Closing ATM Session." << endl;
	std::cout << "======================================" << endl;
	write_Transac_history(session_transac_history, session_transac_history_kor);
	called_session_num += 1;
}

void Atm_SingleBank::session_Admin_Kor(Card* c) {
	std::cout << "======================================" << endl;
	std::cout << primary_bank->bank_Name() + " ATM 관리자 세션에 온 것을 환영합니다." << endl;
	std::cout << "======================================" << endl;
	string session_transac_history = "Admin Session : " + to_string(called_session_num) + "\n";
	string session_transac_history_kor = "관리자 세션 : " + to_string(called_session_num) + "\n";
	// 바로 메뉴 하나를 보여준다. 
	try {
		if (c->bank_Name() != primary_bank->bank_Name()) {
			throw Primary_exception();
		}
		do {
			int select_num = 0;
			std::cout << "======================================" << endl;
			std::cout << primary_bank->bank_Name() + " ATM " + to_string(atm_serial) + " 관리자 메뉴" << endl;
			std::cout << "원하는 메뉴를 선택하세요." << endl;
			std::cout << "1. 거래기록 열람" << endl;
			std::cout << "2. 종료" << endl;
			std::cout << "======================================" << endl;
			cin >> select_num;
			try {
				if (cin.fail()) {
					throw Cin_exception();
				}
				if (select_num == 1) {
					// 거래기록 파일 내보내기
					ofstream fout;
					string output_filename = primary_bank->bank_Name() + " ATM " + to_string(atm_serial) + " transac_history_kor.txt";
					fout.open(output_filename);
					try {
						if (!fout) {
							throw File_open_fail();
						}
						fout << primary_bank->bank_Name() + " ATM " + to_string(atm_serial) + " 거래 기록\n";
						fout << transac_history_kor;
						std::cout << "======================================" << endl;
						std::cout << "거래 기록 출력에 성공했습니다." << endl;
						std::cout << "======================================" << endl;
						fout.close();
					}
					catch (File_open_fail) {
						std::cout << "======================================" << endl;
						std::cout << "거래 기록 출력에 실패했습니다." << endl;
						std::cout << "======================================" << endl;
						fout.close();
					}
					std::cout << "======================================" << endl;
					std::cout << "ATM에서 일어난 거래는 다음과 같습니다 : " << endl;
					std::cout << transac_history_kor << endl;
					std::cout << "======================================" << endl;
					session_transac_history += "ATM transaction history viewed\n";
					session_transac_history_kor += "ATM 거래기록 조회됨\n";
				}
				else if (select_num == 2) {
					break;
				}
				else {
					throw Num_exception();
				}
			}
			catch (Cin_exception) {
				// cin에 잘못된 자료형이 들어가면 cin의 버퍼를 지워줘야 다음 while문에서 cin를 사용시 infinite loop가 발생하지 않는다.
				std::cout << "======================================" << endl;
				std::cout << "문자 외에 숫자 1 또는 2를 입력하세요." << endl;
				std::cout << "======================================" << endl;
				// cin의 버퍼를 지워주는 부분
				cin.clear();
				cin.ignore(256, '\n');
			}
			catch (Num_exception) {
				std::cout << "======================================" << endl;
				std::cout << "숫자 1 또는 2를 입력하세요." << endl;
				std::cout << "======================================" << endl;
			}
		} while (true);
	}
	catch (Primary_exception) {
		std::cout << "======================================" << endl;
		cout << "유효하지 않은 관리자 카드입니다." << endl;
		std::cout << "======================================" << endl;
		session_transac_history += "Admin Session terminated : Invalid Admin Card used.\n";
		session_transac_history_kor += "관리자 세션 종료 : 유효하지 않은 관리자 카드가 사용되었습니다.\n";
	}
	// 세션이 종료됨.
	std::cout << "======================================" << endl;
	std::cout << "ATM 세션을 종료합니다." << endl;
	std::cout << "======================================" << endl;
	write_Transac_history(session_transac_history, session_transac_history_kor);
	called_session_num += 1;
}


// Multi Bank Atm을 나타내는 class : Atm에서 상속됨
class Atm_MultiBank : public Atm {
public:
	// 생성자 : 시리얼번호, Primary Bank, SBA, UL 여부를 입력받음
	Atm_MultiBank(int a_serial, Bank* p_bank, bool ul, int* lf_cash);
	// 현금을 받거나 줄때는 금액 종류별로 몇장을 받을 건지 물어보자. 재고 반영은 몇장씩 주고 받는 걸로 해결.
	// 입금을 구현 : a에서 리턴값만큼 입금 : 표시되는 언어는 영어다
	int Deposit(Account* a);
	// 출금을 구현 : a에서 리턴값만큼 출금 : 표시되는 언어는 영어다
	int Withdrawal(Account* a);
	// 송금을 구현 : a1에서 a2에게 리턴값만큼 송금 : 표시되는 언어는 영어다.
	int Transfer(Account* a1, Account* a2);
	// 입력받은 비밀번호를 체크하는 부분. 맞으면 True, 세 번 이상 틀리면 False를 반환 : 표시되는 언어는 영어다.
	bool user_Authorize(Account* a);
	// 입금을 구현 : a에서 리턴값만큼 입금 : 표시되는 언어는 한국어다
	int Deposit_Kor(Account* a);
	// 출금을 구현 : a에서 리턴값만큼 출금 : 표시되는 언어는 한국어다
	int Withdrawal_Kor(Account* a);
	// 송금을 구현 : a1에서 a2에게 리턴값만큼 송금 : 표시되는 언어는 한국어다.
	int Transfer_Kor(Account* a1, Account* a2);
	// 입력받은 비밀번호를 체크하는 부분. 맞으면 True, 세 번 이상 틀리면 False를 반환 : 표시되는 언어는 한국어다.
	bool user_Authorize_Kor(Account* a);
	// session 
	void session_Start(Card* c);
	void session_Main(Card* c);
	void session_Main_Kor(Card* c);
	void session_Admin(Card* c);
	void session_Admin_Kor(Card* c);
};

Atm_MultiBank::Atm_MultiBank(int a_serial, Bank* p_bank, bool ul, int* lf_cash) {
	atm_serial = a_serial;
	primary_bank = p_bank;
	is_ul = ul;
	for (int i = 0; i < 4; i++) {
		left_cash[i] = lf_cash[i];
	}
}

int Atm_MultiBank::Deposit(Account* a) {
	int button{ 0 }; // 메뉴 선택 버튼
	// 현금 입력 시 지폐 별 개수 저장, 수표 개수 저장
	int won_1{ 0 }, won_5{ 0 }, won_10{ 0 }, won_50{ 0 }, num_of_check{ 0 };
	int total_amount{ 0 }; // 총 투입 금액
	bool is_a_primary = this->primary_bank->bank_Name() == a->account_Bank(); //a primary 검사;
	// 예외 발생 시 처음 Deposit 상태로 돌아오기 위해 무한 루프로 구현
	while (1) {
		cout << "======================================" << endl;
		cout << "Select type of money" << endl;
		cout << "Select a number" << endl;
		cout << "======================================" << endl;
		cout << "|  1. Cash  |  2. Check  |  3. Exit  |" << endl;
		cout << "======================================" << endl;
		cin >> button;
		// Cash 선택 시
		if (button == 1) {
			cout << "======================================" << endl;
			cout << "Please enter the number of bills" << endl;
			cout << "You can put up to " + to_string(this->getable_cash_num) + " bills." << endl;
			cout << "======================================" << endl;
			cout << "Enter num of KRW 1,000 :";
			cin >> won_1;
			cout << "Enter num of KRW 5,000 :";
			cin >> won_5;
			cout << "Enter num of KRW 10,000 :";
			cin >> won_10;
			cout << "Enter num of KRW 50,000 :";
			cin >> won_50;
			// ATM이 수용 가능한 지폐 개수 초과시 에러 메세지 출력 및 Deposit 재실행
			if (won_1 + won_5 + won_10 + won_50 > this->getable_cash_num) {
				button = won_1 = won_5 = won_10 = won_50 = 0;
				cout << "======================================" << endl;
				cout << "Error : The total number of bills accepted has been exceeded" << endl;
				cout << "======================================" << endl;
				continue;
			}
			total_amount = 1000 * won_1 + 5000 * won_5 + 10000 * won_10 + 50000 * won_50;
			if (is_a_primary) {
				cout << "======================================" << endl;
				cout << "A fee of KRW " + to_string(this->fee_deposit_primary) + " was incurred" << endl;
				cout << "======================================" << endl;
				if (total_amount <= this->fee_deposit_primary) {
					cout << "======================================" << endl;
					cout << "Error: The amount is equal to or less than the fee" << endl;
					cout << "======================================" << endl;
					button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
					continue;
				}
				// ATM 지폐 개수 및 Account 잔액 update
				a->account_Deposit(total_amount - this->fee_deposit_primary);
				this->left_cash[0] += won_1;
				this->left_cash[1] += won_5;
				this->left_cash[2] += won_10;
				this->left_cash[3] += won_50;
				return total_amount - this->fee_deposit_primary;
			}
			else {
				cout << "======================================" << endl;
				cout << "A fee of KRW " + to_string(this->fee_deposit_non_primary) + " was incurred" << endl;
				cout << "======================================" << endl;
				if (total_amount <= this->fee_deposit_non_primary) {
					cout << "======================================" << endl;
					cout << "Error: The amount is equal to or less than the fee" << endl;
					cout << "======================================" << endl;
					button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
					continue;
				}
				// ATM 지폐 개수 및 Account 잔액 update
				a->account_Deposit(total_amount - this->fee_deposit_non_primary);
				this->left_cash[0] += won_1;
				this->left_cash[1] += won_5;
				this->left_cash[2] += won_10;
				this->left_cash[3] += won_50;
				return total_amount - this->fee_deposit_non_primary;
			}
		}
		// Check 선택 시
		else if (button == 2) {
			cout << "======================================" << endl;
			cout << "Please enter the amount of check" << endl;
			cout << "======================================" << endl;
			cout << "amount of check : ";
			cin >> total_amount;
			cout << "======================================" << endl;
			cout << "Please enter the number of check" << endl;
			cout << "You can put up to " + to_string(this->getable_check_num) + " checks." << endl;
			cout << "======================================" << endl;
			cout << "num of check :";
			cin >> num_of_check;
			// ATM이 수용 가능한 수표 개수 초과시 에러 메세지 출력 및 Deposit 재실행
			if (num_of_check > this->getable_check_num) {
				total_amount = 0;
				num_of_check = 0;
				button = 0;
				cout << "======================================" << endl;
				cout << "Error : The total number of checks accepted has been exceeded" << endl;
				cout << "======================================" << endl;
				continue;
			}
			// Account 잔액 update
			total_amount = total_amount * num_of_check;
			if (is_a_primary) {
				cout << "======================================" << endl;
				cout << "A fee of KRW " + to_string(this->fee_deposit_primary) + " was incurred" << endl;
				cout << "======================================" << endl;
				if (total_amount <= this->fee_deposit_primary) {
					cout << "======================================" << endl;
					cout << "Error: The amount is equal to or less than the fee" << endl;
					cout << "======================================" << endl;
					button = total_amount = num_of_check = 0;
					continue;
				}
				a->account_Deposit(total_amount - this->fee_deposit_primary);
				return total_amount - this->fee_deposit_primary;
			}
			else {
				cout << "======================================" << endl;
				cout << "A fee of KRW " + to_string(this->fee_deposit_non_primary) + " was incurred" << endl;
				cout << "======================================" << endl;
				if (total_amount <= this->fee_deposit_non_primary) {
					cout << "======================================" << endl;
					cout << "Error: The amount is equal to or less than the fee" << endl;
					cout << "======================================" << endl;
					button = total_amount = num_of_check = 0;
					continue;
				}
				a->account_Deposit(total_amount - this->fee_deposit_non_primary);
				return total_amount - this->fee_deposit_non_primary;
			}
		}
		// Exit 선택 시 
		else if (button == 3) {
			cout << "======================================" << endl;
			cout << "Exit Deposit" << endl;
			cout << "======================================" << endl;
			return -1;
		}
		// 그 외 다른 button이 눌렸을 시 에러 메시지 출력 및 Deposit 재실행
		else {
			cout << "======================================" << endl;
			cout << "Error : Invalid Input" << endl;
			cout << "Please select type of money again" << endl;
			cout << "======================================" << endl;
			continue;
		}
	}
}

int Atm_MultiBank::Withdrawal(Account* a) {
	int button{ 0 };
	// 출금하고자 하는 지폐 별 개수 저장
	int won_1{ 0 }, won_5{ 0 }, won_10{ 0 }, won_50{ 0 };
	int total_amount{ 0 }; // 총 출금 금액
	int ATM_amount = 1000 * this->left_cash[0] + 5000 * this->left_cash[1] + 10000 * this->left_cash[2] + 50000 * this->left_cash[3];
	int amount{ 0 };
	bool is_a_primary = this->primary_bank->bank_Name() == a->account_Bank(); //a primary 검사;
	// 예외 발생 시 처음 Withdrawal 상태로 돌아오기 위해 무한 루프로 구현
	while (1) {
		cout << "======================================" << endl;
		cout << "Withdrawal Menu" << endl;
		cout << "=========================" << endl;
		cout << "|  1. Start |  2. Exit  |" << endl;
		cout << "=========================" << endl;
		cin >> button;
		if (button == 1) {
			cout << "======================================" << endl;
			cout << "Please enter the amount of money(ATM balance : KRW " + to_string(ATM_amount) + ")" << endl;
			cout << "You can withdraw up to KRW " + to_string(this->withdrawal_amount) + " at one time." << endl;
			cout << "======================================" << endl;
			cout << "amount of money :";
			cin >> total_amount;
			if (total_amount > ATM_amount) {
				cout << "======================================" << endl;
				cout << "Error : The ATM balance is insufficient to withdraw money" << endl;
				cout << "======================================" << endl;
				button = total_amount = 0;
				continue;
			}
			if (total_amount > this->withdrawal_amount) {
				cout << "======================================" << endl;
				cout << "Error : You have exceeded the amount that can be withdrawn at one time" << endl;
				cout << "======================================" << endl;
				button = total_amount = 0;
				continue;
			}
			cout << "======================================" << endl;
			cout << "Please enter the number of bills" << endl;
			cout << "You can take out KRW 1,000 bills up to " + to_string(this->left_cash[0]) << endl;
			cout << "You can take out KRW 5,000 bills up to " + to_string(this->left_cash[1]) << endl;
			cout << "You can take out KRW 10,000 bills up to " + to_string(this->left_cash[2]) << endl;
			cout << "You can take out KRW 50,000 bills up to " + to_string(this->left_cash[3]) << endl;
			cout << "======================================" << endl;
			cout << "Enter num of KRW 1,000 :";
			cin >> won_1;
			cout << "Enter num of KRW 5,000 :";
			cin >> won_5;
			cout << "Enter num of KRW 10,000 :";
			cin >> won_10;
			cout << "Enter num of KRW 50,000 :";
			cin >> won_50;
			if ((won_1 > this->left_cash[0]) || (won_5 > this->left_cash[1]) || (won_10 > this->left_cash[2]) || (won_50 > this->left_cash[3])) {
				cout << "======================================" << endl;
				cout << "Error : The requested number of bills cannot be withdrawn." << endl;
				cout << "======================================" << endl;
				button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
				continue;
			}
			amount = won_1 * 1000 + won_5 * 5000 + won_10 * 10000 + won_50 * 50000;
			if (total_amount != amount) {
				cout << "======================================" << endl;
				cout << "Error : It does not match the amount you wish to withdraw." << endl;
				cout << "======================================" << endl;
				button = total_amount = amount = won_1 = won_5 = won_10 = won_50 = 0;
				continue;
			}
			if (total_amount > a->account_Balance()) {
				cout << "======================================" << endl;
				cout << "Error : Insufficient account balance" << endl;
				cout << "======================================" << endl;
				button = total_amount = amount = won_1 = won_5 = won_10 = won_50 = 0;
				continue;
			}
			//계좌 은행이 primary bank일때 
			if (is_a_primary) {
				cout << "======================================" << endl;
				cout << "A fee of KRW " + to_string(this->fee_withdrawal_primary) + " was incurred" << endl;
				cout << "======================================" << endl;
				if (total_amount + fee_withdrawal_primary > a->account_Balance()) {
					cout << "======================================" << endl;
					cout << "Error : Insufficient account balance" << endl;
					cout << "======================================" << endl;
					button = total_amount = amount = won_1 = won_5 = won_10 = won_50 = 0;
					continue;
				}
				a->account_Withdrawl(total_amount + fee_withdrawal_primary);
				this->left_cash[0] -= won_1;
				this->left_cash[1] -= won_5;
				this->left_cash[2] -= won_10;
				this->left_cash[3] -= won_50;
				return total_amount;
			}
			//계좌 은행이 primary bank가 아닐때
			else {
				cout << "======================================" << endl;
				cout << "A fee of KRW " + to_string(this->fee_withdrawal_non_primary) + " was incurred" << endl;
				cout << "======================================" << endl;
				if (total_amount + fee_withdrawal_non_primary > a->account_Balance()) {
					cout << "======================================" << endl;
					cout << "Error : Insufficient account balance" << endl;
					cout << "======================================" << endl;
					button = total_amount = amount = won_1 = won_5 = won_10 = won_50 = 0;
					continue;
				}
				a->account_Withdrawl(total_amount + fee_withdrawal_non_primary);
				this->left_cash[0] -= won_1;
				this->left_cash[1] -= won_5;
				this->left_cash[2] -= won_10;
				this->left_cash[3] -= won_50;
				return total_amount;
			}
		}
		else if (button == 2) {
			cout << "======================================" << endl;
			cout << "Exit Withdrawal" << endl;
			cout << "======================================" << endl;
			return -1;
		}
		else {
			cout << "======================================" << endl;
			cout << "Error : Invalid Input" << endl;
			cout << "Please select menu again" << endl;
			cout << "======================================" << endl;
			continue;
		}
	}
}

int Atm_MultiBank::Transfer(Account* a1, Account* a2) {
	int button{ 0 }; // 메뉴 선택 버튼
	int verify_button{ 0 }; // 현금 송금 확인 버튼
	// 현금 입력 시 지폐 별 개수 저장, 수표 개수 저장
	int won_1{ 0 }, won_5{ 0 }, won_10{ 0 }, won_50{ 0 };
	int total_amount{ 0 }; // 총 투입 금액
	bool is_a1_primary = this->primary_bank->bank_Name() == a1->account_Bank(); //a1 primary 검사
	bool is_a2_primary = this->primary_bank->bank_Name() == a2->account_Bank(); //a2 primary 검사
	// 예외 발생 시 처음 Deposit 상태로 돌아오기 위해 무한 루프로 구현
	while (1) {
		// Transfer을 시작할지 안할지 선택
		cout << "======================================" << endl;
		cout << "Select type of transfer" << endl;
		cout << "Select a number" << endl;
		cout << "=======================================================" << endl;
		cout << "|  1. Cash Transfer |  2. Bank Transfer  |  3. Exit  |" << endl;
		cout << "=======================================================" << endl;
		cin >> button;
		// Cash 선택 시
		if (button == 1) {
			cout << "======================================" << endl;
			cout << "Please enter the number of bills" << endl;
			cout << "You can put up to " + to_string(this->getable_cash_num) + " bills." << endl;
			cout << "======================================" << endl;
			cout << "Enter num of KRW 1,000 :";
			cin >> won_1;
			cout << "Enter num of KRW 5,000 :";
			cin >> won_5;
			cout << "Enter num of KRW 10,000 :";
			cin >> won_10;
			cout << "Enter num of KRW 50,000 :";
			cin >> won_50;
			// ATM이 수용 가능한 지폐 개수 초과시 에러 메세지 출력 및 Deposit 재실행
			if (won_1 + won_5 + won_10 + won_50 > this->getable_cash_num) {
				button = won_1 = won_5 = won_10 = won_50 = 0;
				cout << "======================================" << endl;
				cout << "Error : The total number of bills accepted has been exceeded" << endl;
				cout << "======================================" << endl;
				continue;
			}
			// ATM 지폐 개수 및 Account 잔액 update
			total_amount = 1000 * won_1 + 5000 * won_5 + 10000 * won_10 + 50000 * won_50;
			cout << "Would you like to transfer KRW " + to_string(total_amount) << endl;
			cout << "========================" << endl;
			cout << "|  1. Yes  |  2. No  |" << endl;
			cout << "========================" << endl;
			cin >> verify_button;
			if (verify_button != 1) {
				verify_button = button = won_1 = won_5 = won_10 = won_50 = 0;
				cout << "Go back to the beginning menu" << endl;
				continue;
			}
			// a1 은행이 primary bank인 경우
			if (is_a1_primary) {
				// a2 은행이 primary bank인 경우
				if (is_a2_primary) {
					cout << "======================================" << endl;
					cout << "A fee of KRW " + to_string(this->fee_transfer_primary_primary) + " was incurred" << endl;
					cout << "======================================" << endl;
					// ATM에 투입한 금액이 수수료보다 작을 때
					if (total_amount < fee_transfer_primary_primary) {
						cout << "======================================" << endl;
						cout << "Error : The amount is less than the fee" << endl;
						cout << "======================================" << endl;
						button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
						continue;
					}
					a2->account_Deposit(total_amount - fee_transfer_primary_primary);
					this->left_cash[0] += won_1;
					this->left_cash[1] += won_5;
					this->left_cash[2] += won_10;
					this->left_cash[3] += won_50;
					return total_amount - fee_transfer_primary_primary;
				}
				// a2 은행이 another bank인 경우
				else {
					cout << "======================================" << endl;
					cout << "A fee of KRW " + to_string(this->fee_transfer_primary_non_primary) + " was incurred" << endl;
					cout << "======================================" << endl;
					// ATM에 투입한 금액이 수수료보다 작을 때
					if (total_amount < fee_transfer_primary_non_primary) {
						cout << "======================================" << endl;
						cout << "Error : The amount is less than the fee" << endl;
						cout << "======================================" << endl;
						button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
						continue;
					}
					a2->account_Deposit(total_amount - fee_transfer_primary_non_primary);
					this->left_cash[0] += won_1;
					this->left_cash[1] += won_5;
					this->left_cash[2] += won_10;
					this->left_cash[3] += won_50;
					return total_amount - fee_transfer_primary_non_primary;
				}
			}
			// a1 은행이 another bank인 경우
			else {
				// a2 은행이 primary bank인 경우
				if (is_a2_primary) {
					cout << "======================================" << endl;
					cout << "A fee of KRW " + to_string(this->fee_transfer_primary_non_primary) + " was incurred" << endl;
					cout << "======================================" << endl;
					// ATM에 투입한 금액이 수수료보다 작을 때
					if (total_amount < fee_transfer_primary_non_primary) {
						cout << "======================================" << endl;
						cout << "Error : The amount is less than the fee" << endl;
						cout << "======================================" << endl;
						button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
						continue;
					}
					a2->account_Deposit(total_amount - fee_transfer_primary_non_primary);
					this->left_cash[0] += won_1;
					this->left_cash[1] += won_5;
					this->left_cash[2] += won_10;
					this->left_cash[3] += won_50;
					return total_amount - fee_transfer_primary_non_primary;
				}
				// a2 은행이 another bank인 경우
				else {
					cout << "======================================" << endl;
					cout << "A fee of KRW " + to_string(this->fee_transfer_non_primary_non_primary) + " was incurred" << endl;
					cout << "======================================" << endl;
					// ATM에 투입한 금액이 수수료보다 작을 때
					if (total_amount < fee_transfer_non_primary_non_primary) {
						cout << "======================================" << endl;
						cout << "Error : The amount is less than the fee" << endl;
						cout << "======================================" << endl;
						button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
						continue;
					}
					a2->account_Deposit(total_amount - fee_transfer_non_primary_non_primary);
					this->left_cash[0] += won_1;
					this->left_cash[1] += won_5;
					this->left_cash[2] += won_10;
					this->left_cash[3] += won_50;
					return total_amount - fee_transfer_non_primary_non_primary;
				}
			}
		}
		// Bank 선택 시
		else if (button == 2) {
			cout << "======================================" << endl;
			cout << "Please enter the amount of money" << endl;
			cout << "======================================" << endl;
			cout << "amount of money : ";
			cin >> total_amount;
			// 송금 금액이 a1 계좌의 잔액보다 많은 경우
			if (total_amount > a1->account_Balance()) {
				cout << "======================================" << endl;
				cout << "Error : Insufficient account balance" << endl;
				cout << "======================================" << endl;
				button = total_amount = 0;
				continue;
			}
			// a1 은행이 primary bank인 경우
			if (is_a1_primary) {
				// a2 은행이 primary bank인 경우
				if (is_a2_primary) {
					cout << "======================================" << endl;
					cout << "A fee of KRW " + to_string(this->fee_deposit_primary) + " was incurred" << endl;
					cout << "======================================" << endl;
					// 송금 금액과 수수료 합이 계좌 잔액보다 클때
					if (total_amount + 2000 > a1->account_Balance()) {
						cout << "======================================" << endl;
						cout << "Error : The sum of the withdrawal amount and fee exceeds account balance" << endl;
						cout << "======================================" << endl;
						button = total_amount = 0;
						continue;
					}
					a1->account_Withdrawl(total_amount + 2000);
					a2->account_Deposit(total_amount);
					return total_amount;
				}
				// a2 은행이 another bank인 경우
				else {
					cout << "======================================" << endl;
					cout << "A fee of KRW " + to_string(this->fee_deposit_primary) + " was incurred" << endl;
					cout << "======================================" << endl;
					// 송금 금액과 수수료 합이 계좌 잔액보다 클때
					if (total_amount + 3000 > a1->account_Balance()) {
						cout << "======================================" << endl;
						cout << "Error : The sum of the withdrawal amount and fee exceeds account balance" << endl;
						cout << "======================================" << endl;
						button = total_amount = 0;
						continue;
					}
					a1->account_Withdrawl(total_amount + 3000);
					a2->account_Deposit(total_amount);
					return total_amount;
				}
			}
			// a1 은행이 another bank인 경우
			else {
				// a2 은행이 primary bank인 경우
				if (is_a2_primary) {
					cout << "======================================" << endl;
					cout << "A fee of KRW " + to_string(this->fee_deposit_primary) + " was incurred" << endl;
					cout << "======================================" << endl;
					// 송금 금액과 수수료 합이 계좌 잔액보다 클때
					if (total_amount + 3000 > a1->account_Balance()) {
						cout << "======================================" << endl;
						cout << "Error : The sum of the withdrawal amount and fee exceeds account balance" << endl;
						cout << "======================================" << endl;
						button = total_amount = 0;
						continue;
					}
					a1->account_Withdrawl(total_amount + 3000);
					a2->account_Deposit(total_amount);
					return total_amount;
				}
				// a2 은행이 another bank인 경우
				else {
					cout << "======================================" << endl;
					cout << "A fee of KRW " + to_string(this->fee_deposit_primary) + " was incurred" << endl;
					cout << "======================================" << endl;
					// 송금 금액과 수수료 합이 계좌 잔액보다 클때
					if (total_amount + 4000 > a1->account_Balance()) {
						cout << "======================================" << endl;
						cout << "Error : The sum of the withdrawal amount and fee exceeds account balance" << endl;
						cout << "======================================" << endl;
						button = total_amount = 0;
						continue;
					}
					a1->account_Withdrawl(total_amount + 4000);
					a2->account_Deposit(total_amount);
					return total_amount;
				}
			}
		}
		// Exit 선택 시 
		else if (button == 3) {
			cout << "======================================" << endl;
			cout << "Exit Transfer" << endl;
			cout << "======================================" << endl;
			return -1;
		}
		// 그 외 다른 button이 눌렸을 시 에러 메시지 출력 및 Deposit 재실행
		else {
			cout << "======================================" << endl;
			cout << "Error : Invalid Input" << endl;
			cout << "Please select type of transfer again" << endl;
			cout << "======================================" << endl;
			continue;
		}
	}
}

bool Atm_MultiBank::user_Authorize(Account* a) {
	int pw{ 0 };
	int wrong_count{ 3 };
	while (1) {
		cout << "======================================" << endl;
		cout << "Please enter a password :";
		cin >> pw;
		cout << "======================================" << endl;
		if (pw != a->account_Password()) {
			pw = 0;
			wrong_count -= 1;
			cout << "======================================" << endl;
			cout << "Error : Incorrect password" << endl;
			cout << "======================================" << endl;
			if (wrong_count == 0) {
				cout << "======================================" << endl;
				cout << "You have no more chances left" << endl;
				cout << "======================================" << endl;
				return false;
			}
			cout << "======================================" << endl;
			cout << "You have " + to_string(wrong_count) + " chances left." << endl;
			cout << "======================================" << endl;
			continue;
		}
		return true;
	}
}

int Atm_MultiBank::Deposit_Kor(Account* a) {
	int button{ 0 }; // 메뉴 선택 버튼
	// 현금 입력 시 지폐 별 개수 저장, 수표 개수 저장
	int won_1{ 0 }, won_5{ 0 }, won_10{ 0 }, won_50{ 0 }, num_of_check{ 0 };
	int total_amount{ 0 }; // 총 투입 금액
	bool is_a_primary = this->primary_bank->bank_Name() == a->account_Bank(); //a primary 검사;
	// 예외 발생 시 처음 Deposit 상태로 돌아오기 위해 무한 루프로 구현
	while (1) {
		cout << "======================================" << endl;
		cout << "입금하고자 하는 돈의 유형을 선택하세요" << endl;
		cout << "메뉴 선택은 번호를 입력해주세요" << endl;
		cout << "======================================" << endl;
		cout << "|  1. 현금  |  2. 수표  |  3. 나가기  |" << endl;
		cout << "======================================" << endl;
		cin >> button;
		// Cash 선택 시
		if (button == 1) {
			cout << "======================================" << endl;
			cout << "입금하고자 하는 현금의 지폐수를 입력해주세요" << endl;
			cout << "한 번에 최대 " + to_string(this->getable_cash_num) + " 장까지 처리 가능합니다" << endl;
			cout << "======================================" << endl;
			cout << "1,000원 장수를 입력하세요 :";
			cin >> won_1;
			cout << "5,000원 장수를 입력하세요 :";
			cin >> won_5;
			cout << "10,000원 장수를 입력하세요 :";
			cin >> won_10;
			cout << "50,000원 장수를 입력하세요 :";
			cin >> won_50;
			// ATM이 수용 가능한 지폐 개수 초과시 에러 메세지 출력 및 Deposit 재실행
			if (won_1 + won_5 + won_10 + won_50 > this->getable_cash_num) {
				button = won_1 = won_5 = won_10 = won_50 = 0;
				cout << "======================================" << endl;
				cout << "오류 : ATM이 한 번에 처리할 수 있는 지폐의 장수를 초과하였습니다" << endl;
				cout << "======================================" << endl;
				continue;
			}
			total_amount = 1000 * won_1 + 5000 * won_5 + 10000 * won_10 + 50000 * won_50;
			if (is_a_primary) {
				cout << "======================================" << endl;
				cout << "수수료가 " + to_string(this->fee_deposit_primary) + "원 발생했습니다" << endl;
				cout << "======================================" << endl;
				if (total_amount <= fee_deposit_primary) {
					cout << "======================================" << endl;
					cout << "오류 : 입금 금액이 수수료보다 같거나 작습니다" << endl;
					cout << "======================================" << endl;
					button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
					continue;
				}
				// ATM 지폐 개수 및 Account 잔액 update
				a->account_Deposit(total_amount - fee_deposit_primary);
				this->left_cash[0] += won_1;
				this->left_cash[1] += won_5;
				this->left_cash[2] += won_10;
				this->left_cash[3] += won_50;
				return total_amount - fee_deposit_primary;
			}
			//계정 은행이 another bank일 경우 : 수수료 1000원
			else {
				cout << "======================================" << endl;
				cout << "수수료가 " + to_string(this->fee_deposit_non_primary) + "원 발생했습니다" << endl;
				cout << "======================================" << endl;
				if (total_amount <= fee_deposit_non_primary) {
					cout << "======================================" << endl;
					cout << "오류 : 입금 금액이 수수료보다 같거나 작습니다" << endl;
					cout << "======================================" << endl;
					button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
					continue;
				}
				// ATM 지폐 개수 및 Account 잔액 update
				a->account_Deposit(total_amount - fee_deposit_non_primary);
				this->left_cash[0] += won_1;
				this->left_cash[1] += won_5;
				this->left_cash[2] += won_10;
				this->left_cash[3] += won_50;
				return total_amount - fee_deposit_non_primary;
			}
		}
		// Check 선택 시
		else if (button == 2) {
			cout << "======================================" << endl;
			cout << "입금하고자 하는 수표의 액수를 입력하세요" << endl;
			cout << "======================================" << endl;
			cout << "수표 액수 : ";
			cin >> total_amount;
			cout << "======================================" << endl;
			cout << "입금하고자 하는 수표의 장수를 입력하세요" << endl;
			cout << "한 번에 최대 " + to_string(this->getable_check_num) + " 장의 수표가 처리 가능합니다" << endl;
			cout << "======================================" << endl;
			cout << "수표 장수 :";
			cin >> num_of_check;
			// ATM이 수용 가능한 수표 개수 초과시 에러 메세지 출력 및 Deposit 재실행
			if (num_of_check > this->getable_check_num) {
				total_amount = 0;
				num_of_check = 0;
				button = 0;
				cout << "======================================" << endl;
				cout << "오류 : ATM이 한 번에 처리할 수 있는 수표의 장수를 초과하였습니다." << endl;
				cout << "======================================" << endl;
				continue;
			}
			// Account 잔액 update
			total_amount = total_amount * num_of_check;
			if (is_a_primary) {
				cout << "======================================" << endl;
				cout << "수수료가 " + to_string(this->fee_deposit_primary) + "원 발생했습니다" << endl;
				cout << "======================================" << endl;
				if (total_amount <= fee_deposit_primary) {
					cout << "======================================" << endl;
					cout << "오류 : 입금 금액이 수수료보다 같거나 작습니다" << endl;
					cout << "======================================" << endl;
					button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
					continue;
				}
				a->account_Deposit(total_amount - fee_deposit_primary);
				return total_amount - fee_deposit_primary;
			}
			//계정 은행이 another bank일 경우 : 수수료 1000원
			else {
				cout << "======================================" << endl;
				cout << "수수료가 " + to_string(this->fee_deposit_non_primary) + "원 발생했습니다" << endl;
				cout << "======================================" << endl;
				if (total_amount <= fee_deposit_non_primary) {
					cout << "======================================" << endl;
					cout << "오류 : 입금 금액이 수수료보다 같거나 작습니다" << endl;
					cout << "======================================" << endl;
					button = total_amount = num_of_check = 0;
					continue;
				}
				a->account_Deposit(total_amount - fee_deposit_non_primary);
				return total_amount - fee_deposit_non_primary;
			}
		}
		// Exit 선택 시 
		else if (button == 3) {
			cout << "======================================" << endl;
			cout << "입금 메뉴를 종료합니다." << endl;
			cout << "======================================" << endl;
			return -1;
		}
		// 그 외 다른 button이 눌렸을 시 에러 메시지 출력 및 Deposit 재실행
		else {
			cout << "======================================" << endl;
			cout << "오류 : 잘못된 입력입니다" << endl;
			cout << "돈의 유형을 다시 입력해주세요" << endl;
			cout << "======================================" << endl;
			continue;
		}
	}
}

int Atm_MultiBank::Withdrawal_Kor(Account* a) {
	int button{ 0 };
	// 출금하고자 하는 지폐 별 개수 저장
	int won_1{ 0 }, won_5{ 0 }, won_10{ 0 }, won_50{ 0 };
	int total_amount{ 0 }; // 총 출금 금액
	int ATM_amount = 1000 * this->left_cash[0] + 5000 * this->left_cash[1] + 10000 * this->left_cash[2] + 50000 * this->left_cash[3];
	int amount{ 0 };
	bool is_a_primary = this->primary_bank->bank_Name() == a->account_Bank(); //a primary 검사;
	// 예외 발생 시 처음 Withdrawal 상태로 돌아오기 위해 무한 루프로 구현
	while (1) {
		cout << "======================================" << endl;
		cout << "출금 유형을 선택하세요" << endl;
		cout << "번호를 입력하세요" << endl;
		cout << "=========================" << endl;
		cout << "|  1. 시작 |  2. 나가기  |" << endl;
		cout << "=========================" << endl;
		cin >> button;
		if (button == 1) {
			cout << "======================================" << endl;
			cout << "출금 금액을 입력해주세요(ATM 보유잔액 : " + to_string(ATM_amount) + " 원)" << endl;
			cout << "한 번에 최대 " + to_string(this->withdrawal_amount) + "원 출금 가능합니다";
			cout << "======================================" << endl;
			cout << "출금 금액 :";
			cin >> total_amount;
			if (total_amount > ATM_amount) {
				cout << "======================================" << endl;
				cout << "오류 : ATM 보유잔액이 부족합니다." << endl;
				cout << "======================================" << endl;
				button = total_amount = 0;
				continue;
			}
			if (total_amount > this->withdrawal_amount) {
				cout << "======================================" << endl;
				cout << "오류 : 한 번에 출금 가능한 금액을 초과하였습니다" << endl;
				cout << "======================================" << endl;
				button = total_amount = 0;
				continue;
			}
			cout << "======================================" << endl;
			cout << "출금을 원하시는 각 지폐별 개수를 선택해주세요" << endl;
			cout << "1,000원은 최대 " + to_string(this->left_cash[0]) + "장 출금가능" << endl;
			cout << "5,000원은 최대 " + to_string(this->left_cash[1]) + "장 출금가능" << endl;
			cout << "10,000원은 최대 " + to_string(this->left_cash[2]) + "장 출금가능" << endl;
			cout << "50,000원은 최대 " + to_string(this->left_cash[3]) + "장 출금가능" << endl;
			cout << "======================================" << endl;
			cout << "1,000원 장수를 입력해주세요:";
			cin >> won_1;
			cout << "5,000원 장수를 입력해주세요:";
			cin >> won_5;
			cout << "10,000원 장수를 입력해주세요:";
			cin >> won_10;
			cout << "50,000원 장수를 입력해주세요:";
			cin >> won_50;
			if ((won_1 > this->left_cash[0]) || (won_5 > this->left_cash[1]) || (won_10 > this->left_cash[2]) || (won_50 > this->left_cash[3])) {
				cout << "======================================" << endl;
				cout << "오류 : 요청하신 만큼의 지폐를 보유하고 있지 않습니다" << endl;
				cout << "======================================" << endl;
				button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
				continue;
			}
			amount = won_1 * 1000 + won_5 * 5000 + won_10 * 10000 + won_50 * 50000;
			if (total_amount != amount) {
				cout << "======================================" << endl;
				cout << "오류 : 출금을 원하시는 금액과 일치하지 않습니다" << endl;
				cout << "======================================" << endl;
				button = total_amount = amount = won_1 = won_5 = won_10 = won_50 = 0;
				continue;
			}
			if (total_amount > a->account_Balance()) {
				cout << "======================================" << endl;
				cout << "오류 : 계좌잔액이 부족합니다" << endl;
				cout << "======================================" << endl;
				button = total_amount = amount = won_1 = won_5 = won_10 = won_50 = 0;
				continue;
			}
			//계좌 은행이 primary bank일때 
			if (is_a_primary) {
				cout << "======================================" << endl;
				cout << "수수료가 " + to_string(this->fee_withdrawal_primary) + "원 발생했습니다" << endl;
				cout << "======================================" << endl;
				if (total_amount + fee_withdrawal_primary > a->account_Balance()) {
					cout << "======================================" << endl;
					cout << "오류 : 출금 금액과 수수료의 합보다 계좌잔액이 부족합니다" << endl;
					cout << "======================================" << endl;
					button = total_amount = amount = won_1 = won_5 = won_10 = won_50 = 0;
					continue;
				}
				a->account_Withdrawl(total_amount + fee_withdrawal_primary);
				this->left_cash[0] -= won_1;
				this->left_cash[1] -= won_5;
				this->left_cash[2] -= won_10;
				this->left_cash[3] -= won_50;
				return total_amount;
			}
			//계좌 은행이 primary bank가 아닐때
			else {
				cout << "======================================" << endl;
				cout << "수수료가 " + to_string(this->fee_withdrawal_non_primary) + "원 발생했습니다" << endl;
				cout << "======================================" << endl;
				if (total_amount + fee_withdrawal_non_primary > a->account_Balance()) {
					cout << "======================================" << endl;
					cout << "오류 : 출금 금액과 수수료의 합보다 계좌잔액이 부족합니다" << endl;
					cout << "======================================" << endl;
					button = total_amount = amount = won_1 = won_5 = won_10 = won_50 = 0;
					continue;
				}
				a->account_Withdrawl(total_amount + fee_withdrawal_non_primary);
				this->left_cash[0] -= won_1;
				this->left_cash[1] -= won_5;
				this->left_cash[2] -= won_10;
				this->left_cash[3] -= won_50;
				return total_amount;
			}

		}
		else if (button == 2) {
			cout << "======================================" << endl;
			cout << "출금 나가기" << endl;
			cout << "======================================" << endl;
			return -1;
		}
		else {
			cout << "======================================" << endl;
			cout << "오류 : 잘못된 입력입니다" << endl;
			cout << "메뉴를 다시 입력해주세요" << endl;
			cout << "======================================" << endl;
			continue;
		}
	}
}

int Atm_MultiBank::Transfer_Kor(Account* a1, Account* a2) {
	int button{ 0 }; // 메뉴 선택 버튼
	int verify_button{ 0 }; // 현금 송금 확인 버튼
// 현금 입력 시 지폐 별 개수 저장, 수표 개수 저장
	int won_1{ 0 }, won_5{ 0 }, won_10{ 0 }, won_50{ 0 };
	int total_amount{ 0 }; // 총 투입 금액
	bool is_a1_primary = this->primary_bank->bank_Name() == a1->account_Bank(); //a1 primary 검사
	bool is_a2_primary = this->primary_bank->bank_Name() == a2->account_Bank(); //a2 primary 검사
	// 예외 발생 시 처음 Deposit 상태로 돌아오기 위해 무한 루프로 구현
	while (1) {
		// Transfer을 시작할지 안할지 선택
		cout << "======================================" << endl;
		cout << "송금 유형을 선택하세요" << endl;
		cout << "번호를 입력하세요" << endl;
		cout << "=======================================================" << endl;
		cout << "|  1. 현금 이체 |  2. 계좌 이체  |  3. 나가기  |" << endl;
		cout << "=======================================================" << endl;
		cin >> button;
		// Cash 선택 시
		if (button == 1) {
			cout << "======================================" << endl;
			cout << "입금하고자 하는 현금의 지폐수를 입력해주세요" << endl;
			cout << "한 번에 최대 " + to_string(this->getable_cash_num) + " 장까지 처리 가능합니다" << endl;
			cout << "======================================" << endl;
			cout << "1,000원 장수를 입력하세요 :";
			cin >> won_1;
			cout << "5,000원 장수를 입력하세요 :";
			cin >> won_5;
			cout << "10,000원 장수를 입력하세요 :";
			cin >> won_10;
			cout << "50,000원 장수를 입력하세요 :";
			cin >> won_50;
			// ATM이 수용 가능한 지폐 개수 초과시 에러 메세지 출력 및 Deposit 재실행
			if (won_1 + won_5 + won_10 + won_50 > this->getable_cash_num) {
				button = won_1 = won_5 = won_10 = won_50 = 0;
				cout << "======================================" << endl;
				cout << "오류 : ATM이 한 번에 처리할 수 있는 지폐의 장수를 초과하였습니다" << endl;
				cout << "======================================" << endl;
				continue;
			}
			// ATM 지폐 개수 및 Account 잔액 update
			total_amount = 1000 * won_1 + 5000 * won_5 + 10000 * won_10 + 50000 * won_50;
			cout << to_string(total_amount) + "원을 송금하시겠습니까?" << endl;
			cout << "========================" << endl;
			cout << "|  1. 네  |  2. 아니오  |" << endl;
			cout << "========================" << endl;
			cin >> verify_button;
			if (verify_button != 1) {
				verify_button = button = won_1 = won_5 = won_10 = won_50 = 0;
				cout << "처음 메뉴로 돌아갑니다" << endl;
				continue;
			}
			// a1 은행이 primary bank인 경우
			if (is_a1_primary) {
				// a2 은행이 primary bank인 경우
				if (is_a2_primary) {
					cout << "======================================" << endl;
					cout << "수수료가 " + to_string(this->fee_transfer_primary_primary) + "원 발생했습니다" << endl;
					cout << "======================================" << endl;
					// ATM에 투입한 금액이 수수료보다 작을 때
					if (total_amount < fee_transfer_primary_primary) {
						cout << "======================================" << endl;
						cout << "오류 : 송금 금액이 수수료보다 작습니다" << endl;
						cout << "======================================" << endl;
						button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
						continue;
					}
					a2->account_Deposit(total_amount - fee_transfer_primary_primary);
					this->left_cash[0] += won_1;
					this->left_cash[1] += won_5;
					this->left_cash[2] += won_10;
					this->left_cash[3] += won_50;
					return total_amount - fee_transfer_primary_primary;
				}
				// a2 은행이 another bank인 경우
				else {
					cout << "======================================" << endl;
					cout << "수수료가 " + to_string(this->fee_transfer_primary_non_primary) + "원 발생했습니다" << endl;
					cout << "======================================" << endl;
					// ATM에 투입한 금액이 수수료보다 작을 때
					if (total_amount < fee_transfer_primary_non_primary) {
						cout << "======================================" << endl;
						cout << "오류 : 송금 금액이 수수료보다 작습니다" << endl;
						cout << "======================================" << endl;
						button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
						continue;
					}
					a2->account_Deposit(total_amount - fee_transfer_primary_non_primary);
					this->left_cash[0] += won_1;
					this->left_cash[1] += won_5;
					this->left_cash[2] += won_10;
					this->left_cash[3] += won_50;
					return total_amount - fee_transfer_primary_non_primary;
				}
			}
			// a1 은행이 another bank인 경우
			else {
				// a2 은행이 primary bank인 경우
				if (is_a2_primary) {
					cout << "======================================" << endl;
					cout << "수수료가 " + to_string(this->fee_transfer_primary_non_primary) + "원 발생했습니다" << endl;
					cout << "======================================" << endl;
					// ATM에 투입한 금액이 수수료보다 작을 때
					if (total_amount < fee_transfer_primary_non_primary) {
						std::cout << "======================================" << endl;
						std::cout << "오류 : 송금 금액이 수수료보다 작습니다" << endl;
						std::cout << "======================================" << endl;
						button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
						continue;
					}
					a2->account_Deposit(total_amount - fee_transfer_primary_non_primary);
					this->left_cash[0] += won_1;
					this->left_cash[1] += won_5;
					this->left_cash[2] += won_10;
					this->left_cash[3] += won_50;
					return total_amount - fee_transfer_primary_non_primary;
				}
				// a2 은행이 another bank인 경우
				else {
					cout << "======================================" << endl;
					cout << "수수료가 " + to_string(this->fee_transfer_non_primary_non_primary) + "원 발생했습니다" << endl;
					cout << "======================================" << endl;
					// ATM에 투입한 금액이 수수료보다 작을 때
					if (total_amount < fee_transfer_non_primary_non_primary) {
						cout << "======================================" << endl;
						cout << "오류 : 송금 금액이 수수료보다 작습니다" << endl;
						cout << "======================================" << endl;
						button = total_amount = won_1 = won_5 = won_10 = won_50 = 0;
						continue;
					}
					a2->account_Deposit(total_amount - fee_transfer_non_primary_non_primary);
					this->left_cash[0] += won_1;
					this->left_cash[1] += won_5;
					this->left_cash[2] += won_10;
					this->left_cash[3] += won_50;
					return total_amount - fee_transfer_non_primary_non_primary;
				}
			}
		}
		// Bank 선택 시
		else if (button == 2) {
			cout << "======================================" << endl;
			cout << "송금 금액을 입력하세요" << endl;
			cout << "======================================" << endl;
			cout << "송금 금액 : ";
			cin >> total_amount;
			// 송금 금액이 a1 계좌의 잔액보다 많은 경우
			if (total_amount > a1->account_Balance()) {
				cout << "======================================" << endl;
				cout << "오류 : 계좌 잔액이 부족합니다" << endl;
				cout << "======================================" << endl;
				button = total_amount = 0;
				continue;
			}
			// a1 은행이 primary bank인 경우
			if (is_a1_primary) {
				// a2 은행이 primary bank인 경우
				if (is_a2_primary) {
					cout << "======================================" << endl;
					cout << "수수료가 " + to_string(this->fee_transfer_primary_primary) + "원 발생했습니다" << endl;
					cout << "======================================" << endl;
					// 송금 금액과 수수료 합이 계좌 잔액보다 클때
					if (total_amount + fee_transfer_primary_primary > a1->account_Balance()) {
						cout << "======================================" << endl;
						cout << "오류 : 계좌 잔액이 송금 금액과 수수료의 합보다 작습니다" << endl;
						cout << "======================================" << endl;
						button = total_amount = 0;
						continue;
					}
					a1->account_Withdrawl(total_amount + fee_transfer_primary_primary);
					a2->account_Deposit(total_amount);
					return total_amount;
				}
				// a2 은행이 another bank인 경우
				else {
					cout << "======================================" << endl;
					cout << "수수료가 " + to_string(this->fee_transfer_primary_non_primary) + "원 발생했습니다" << endl;
					cout << "======================================" << endl;
					// 송금 금액과 수수료 합이 계좌 잔액보다 클때
					if (total_amount + fee_transfer_primary_non_primary > a1->account_Balance()) {
						cout << "======================================" << endl;
						cout << "오류 : 계좌 잔액이 송금 금액과 수수료의 합보다 작습니다" << endl;
						cout << "======================================" << endl;
						button = total_amount = 0;
						continue;
					}
					a1->account_Withdrawl(total_amount + fee_transfer_primary_non_primary);
					a2->account_Deposit(total_amount);
					return total_amount;
				}
			}
			// a1 은행이 another bank인 경우
			else {
				// a2 은행이 primary bank인 경우
				if (is_a2_primary) {
					cout << "======================================" << endl;
					cout << "수수료가 " + to_string(this->fee_transfer_primary_non_primary) + "원 발생했습니다" << endl;
					cout << "======================================" << endl;
					// 송금 금액과 수수료 합이 계좌 잔액보다 클때
					if (total_amount + fee_transfer_primary_non_primary > a1->account_Balance()) {
						cout << "======================================" << endl;
						cout << "오류 : 계좌 잔액이 송금 금액과 수수료의 합보다 작습니다" << endl;
						cout << "======================================" << endl;
						button = total_amount = 0;
						continue;
					}
					a1->account_Withdrawl(total_amount + fee_transfer_primary_non_primary);
					a2->account_Deposit(total_amount);
					return total_amount;
				}
				// a2 은행이 another bank인 경우
				else {
					cout << "======================================" << endl;
					cout << "수수료가 " + to_string(this->fee_transfer_non_primary_non_primary) + "원 발생했습니다" << endl;
					cout << "======================================" << endl;
					// 송금 금액과 수수료 합이 계좌 잔액보다 클때
					if (total_amount + fee_transfer_non_primary_non_primary > a1->account_Balance()) {
						cout << "======================================" << endl;
						cout << "오류 : 계좌 잔액이 송금 금액과 수수료의 합보다 작습니다" << endl;
						cout << "======================================" << endl;
						button = total_amount = 0;
						continue;
					}
					a1->account_Withdrawl(total_amount + fee_transfer_non_primary_non_primary);
					a2->account_Deposit(total_amount);
					return total_amount;
				}
			}
		}
		// Exit 선택 시 
		else if (button == 3) {
			cout << "======================================" << endl;
			cout << "송금 나가기" << endl;
			cout << "======================================" << endl;
			return -1;
		}
		// 그 외 다른 button이 눌렸을 시 에러 메시지 출력 및 Deposit 재실행
		else {
			cout << "======================================" << endl;
			cout << "오류 : 잘못된 입력" << endl;
			cout << "송금 유형을 다시 선택하세요" << endl;
			cout << "======================================" << endl;
			continue;
		}
	}
}

bool Atm_MultiBank::user_Authorize_Kor(Account* a) {
	int pw{ 0 };
	int wrong_count{ 3 };
	while (1) {
		cout << "======================================" << endl;
		cout << "비밀번호를 입력하세요 :";
		cin >> pw;
		cout << "======================================" << endl;
		if (pw != a->account_Password()) {
			pw = 0;
			wrong_count -= 1;
			cout << "======================================" << endl;
			cout << "오류 : 비밀번호를 잘못 입력하셨습니다" << endl;
			cout << "======================================" << endl;
			if (wrong_count == 0) {
				cout << "======================================" << endl;
				cout << "더 이상 비밀번호를 입력하실 수 없습니다" << endl;
				cout << "======================================" << endl;
				return false;
			}
			cout << "======================================" << endl;
			cout << to_string(wrong_count) + "번의 기회가 남았습니다" << endl;
			cout << "======================================" << endl;
			continue;
		}
		return true;
	}
}

void Atm_MultiBank::session_Start(Card* c) {
	if (is_ul == true) {
		if (c->is_Admin() == true) {
			session_Admin(c);
		}
		else {
			session_Main(c);
		}
	}
	else {
		// 무슨 세션을 선택할 건지 정하는 부분
		int session_indicator = 0;
		while (true) {
			int select_num = 1;
			std::cout << "======================================" << endl;
			std::cout << "Which language do you want to use?" << endl;
			std::cout << "1 : English / 2 : Korean" << endl;
			std::cout << "======================================" << endl;
			cin >> select_num;
			try {
				// cin에서 잘못된 자료형을 받으면 cin.fail()이 true가 된다. 이때 예외처리하면 됨. >> 잘못된 자료형의 경우는 이렇게 처리하면 될 듯.
				if (cin.fail()) {
					throw Cin_exception();
				}
				if (select_num == 1) {
					session_indicator = 1;
					break;
				}
				else if (select_num == 2) {
					session_indicator = 2;
					break;
				}
				// 잘못된 숫자가 들어올 경우 예외처리
				else {
					throw Num_exception();
				}
			}
			catch (Num_exception) {
				std::cout << "======================================" << endl;
				std::cout << "Input only number 1 or 2" << endl;
				std::cout << "======================================" << endl;
			}
			// 잘못된 자료형을 입력했을 때 예외처리
			catch (Cin_exception) {
				// cin에 잘못된 자료형이 들어가면 cin의 버퍼를 지워줘야 다음 while문에서 cin를 사용시 infinite loop가 발생하지 않는다.
				std::cout << "======================================" << endl;
				std::cout << "Input only number 1 or 2. Not Charactor." << endl;
				std::cout << "======================================" << endl;
				// cin의 버퍼를 지워주는 부분
				cin.clear();
				cin.ignore(256, '\n');
			}
		}
		// 영어 세션을 불러온다
		if (session_indicator == 1) {
			if (c->is_Admin() == true) {
				session_Admin(c);
			}
			else {
				session_Main(c);
			}
		}
		// 한글 세션을 불러온다
		else {
			if (c->is_Admin() == true) {
				session_Admin_Kor(c);
			}
			else {
				session_Main_Kor(c);
			}
		}
	}
}

void Atm_MultiBank::session_Main(Card* c) {
	std::cout << "======================================" << endl;
	std::cout << "Welcome to " + primary_bank->bank_Name() + " ATM" << endl;
	std::cout << "======================================" << endl;
	// session에서 이루어지는 모든 거래를 추적해서 기록하는 string을 하나 만든다.
	string session_transac_history = "Session : " + to_string(called_session_num) + "\n";
	string session_transac_history_kor = "세션 : " + to_string(called_session_num) + "\n";
	// account transaction에 더할 거래기록 저장공간
	string session_transac_accountSave = ">> Transactin history in " + primary_bank->bank_Name() + " ATM " + to_string(atm_serial) + "\n";
	string session_transac_accountSave_kor = primary_bank->bank_Name() + " ATM " + to_string(atm_serial) + " 에서 일어난 거래기록\n";
	// 들어온 카드의 Account pointer를 담는 곳
	Account* card_account = nullptr;
	// 출금 횟수를 세는 indicator
	int withdrawal_indicator = 0;
	try {
		// 들어온 카드의 Account pointer를 파악해서 card_account에 넣어야 한다. 만약 없는 Account면 그대로 session을 종료한다.
		Account* temp_account = primary_bank->search_myAccount(c->account_Num());
		if (temp_account == primary_bank->ret_zeroAccount()) {
			temp_account = primary_bank->search_anotherAccount(c->account_Num());
			if (temp_account == primary_bank->ret_zeroAccount()) {
				throw Invalid_account();
			}
			else {
				card_account = temp_account;
			}
		}
		else {
			card_account = temp_account;
		}

		session_transac_history += card_account->account_Num() + "'s transaction history\n";
		session_transac_history_kor += card_account->account_Num() + "의 거래기록\n";

		card_account->transaction_Add(session_transac_accountSave, session_transac_accountSave_kor);

		// 계좌의 비밀번호를 물어본다. 이때 true면 계속 진행하고 false면 예외처리
		bool temp_pw_valid = user_Authorize(card_account);
		if (temp_pw_valid == false) {
			throw Invalid_password();
		}

		// 드디어 실제로 거래를 처리하는 세션까지 왔다.
		do {
			int select_num = 0;
			std::cout << "======================================" << endl;
			std::cout << "Select the option you want to choose" << endl;
			std::cout << "1 : Deposit" << endl;
			std::cout << "2 : Withdrawal" << endl;
			std::cout << "3 : Transfer" << endl;
			std::cout << "4 : Transaction History" << endl;
			std::cout << "5 : Exit" << endl;
			std::cout << "======================================" << endl;
			cin >> select_num;
			try {
				// 잘못된 값이 들어오면 Cin_exception을 던진다. 
				if (cin.fail()) {
					throw Cin_exception();
				}
				if (select_num == 1) {
					int deal_money = Deposit(card_account);
					if (deal_money > 0) {
						// 거래가 끝난 후 거래 내역을 저장하는 곳
						string deposit_history = to_string(deal_money) + "Won added to " + card_account->account_Num() + "\n";
						string deposit_history_kor = to_string(deal_money) + "원이 " + card_account->account_Num() + "에 입금되었습니다." + "\n";
						session_transac_history += deposit_history;
						session_transac_history_kor += deposit_history_kor;
						card_account->transaction_Add(deposit_history, deposit_history_kor);
					}
					else if (deal_money == -1) {
						continue;
					}
				}
				else if (select_num == 2) {
					if (withdrawal_indicator > max_withdrawal) {
						std::cout << "======================================" << endl;
						std::cout << "Your available withdrawal chance is gone." << endl;
						std::cout << "======================================" << endl;
					}
					else {
						int deal_money = Withdrawal(card_account);
						if (deal_money > 0) {
							withdrawal_indicator += 1;
							// 거래가 끝난 후 거래 내역을 저장하는 곳
							string withdrawal_history = to_string(deal_money) + "Won withdrawed from " + card_account->account_Num() + "\n";
							string withdrawal_history_kor = to_string(deal_money) + "원이 " + card_account->account_Num() + "에서 출금되었습니다." + "\n";
							session_transac_history += withdrawal_history;
							session_transac_history_kor += withdrawal_history_kor;
							card_account->transaction_Add(withdrawal_history, withdrawal_history_kor);
						}
						else if (deal_money == -1) {
							continue;
						}
					}
				}
				else if (select_num == 3) {
					// 보낼 계좌번호를 받는 부분
					string temp_sending_account = "";
					Account* temp_sending_accountptr = nullptr;
					do {
						std::cout << "======================================" << endl;
						std::cout << "Which account do you want to send?" << endl;
						std::cout << "======================================" << endl;
						cin >> temp_sending_account;
						try {
							// 계좌번호 자릿수가 맞지 않으면 다시 while문을 돌려야 한다.  
							if (temp_sending_account.length() != 14) {
								throw Invalid_account_num();
							}
							// 계좌번호의 pointer를 찾는다. 존재하지 않는다면 다시 while문을 돌려야 한다.
							temp_sending_accountptr = primary_bank->search_myAccount(temp_sending_account);
							if (temp_sending_accountptr == primary_bank->ret_zeroAccount()) {
								temp_sending_accountptr = primary_bank->search_anotherAccount(temp_sending_account);
								if (temp_sending_accountptr == primary_bank->ret_zeroAccount()) {
									throw Invalid_account();
								}
								else {
									// 실제로 다른 은행에 계좌번호가 존재하는 경우 : break
									break;
								}
							}
							else {
								// 실제로 자기 은행에 계좌번호가 존재하는 경우 : break
								break;
							}
						}
						catch (Invalid_account_num) {
							std::cout << "======================================" << endl;
							std::cout << "Account number is not match" << endl;
							std::cout << "======================================" << endl;
						}
						catch (Invalid_account) {
							std::cout << "======================================" << endl;
							std::cout << "Account is not exist" << endl;
							std::cout << "======================================" << endl;
						}
					} while (true);
					// 받은 계좌번호 포인터를 Transfer함수에 집어넣기
					int deal_money = Transfer(card_account, temp_sending_accountptr);
					if (deal_money > 0) {
						// 거래 내역을 기록한다.
						string transfer_history = to_string(deal_money) + "Won transfered from " + card_account->account_Num() + " to " + temp_sending_accountptr->account_Num() + "\n";
						string transfer_history_kor = to_string(deal_money) + "원이 " + card_account->account_Num() + " 에서 " + temp_sending_accountptr->account_Num() + "으로 송금되었습니다." + "\n";
						string transfer_history_account2 = "transfer from another account : " + transfer_history;
						string transfer_history_account2_kor = "다른 계좌에서 온 송금 : " + transfer_history_kor;
						session_transac_history += transfer_history;
						session_transac_history_kor += transfer_history_kor;
						card_account->transaction_Add(transfer_history, transfer_history_kor);
						temp_sending_accountptr->transaction_Add(transfer_history_account2, transfer_history_account2_kor);
					}
					else if (deal_money == -1) {
						continue;
					}
				}
				else if (select_num == 4) {
					std::cout << "======================================" << endl;
					std::cout << "Account's Bank : " + card_account->account_Bank() << endl;
					std::cout << "Account's User : " + card_account->account_User() << endl;
					std::cout << "Account Number : " + card_account->account_Num() << endl;
					std::cout << "Account Balance : " + to_string(card_account->account_Balance()) << endl;
					std::cout << "Your account transaction history is : \n";
					std::cout << card_account->ret_transac_history(true) << endl;
					std::cout << "======================================" << endl;
				}
				else if (select_num == 5) {
					break;
				}
				else {
					throw Num_exception();
				}
			}
			catch (Cin_exception) {
				// cin에 잘못된 자료형이 들어가면 cin의 버퍼를 지워줘야 다음 while문에서 cin를 사용시 infinite loop가 발생하지 않는다.
				std::cout << "======================================" << endl;
				std::cout << "Input only number 1, 2, 3, 4 or 5. Not Charactor." << endl;
				std::cout << "======================================" << endl;
				// cin의 버퍼를 지워주는 부분
				cin.clear();
				cin.ignore(256, '\n');
			}
			catch (Num_exception) {
				std::cout << "======================================" << endl;
				std::cout << "Input only number 1, 2, 3, 4 or 5" << endl;
				std::cout << "======================================" << endl;
			}
		} while (true);

		// 그 모든 과정을 거치고서도 거래가 성공적으로 완료되었다는 뜻이니 Session을 종료한다. 
		write_Transac_history(session_transac_history, session_transac_history_kor);
		std::cout << "======================================" << endl;
		std::cout << "Account Balance : " + to_string(card_account->account_Balance()) << endl;
		std::cout << "total transaction in this ATM session : \n" + session_transac_history;
		std::cout << "Closing ATM Session." << endl;
		std::cout << "======================================" << endl;
		called_session_num += 1;
	}
	// Card에 있는 account가 없는 account일시 
	catch (Invalid_account) {
		// session_transac_history에 기록할 메시지 작성해서 기록
		session_transac_history += "Session Terminated : Account does not exist\n";
		session_transac_history_kor += "세션 종료 : 존재하지 않는 계좌\n";
		// Session이 종료되었으니 Atm의 transac_history에 session_transac_history를 기록
		write_Transac_history(session_transac_history, session_transac_history_kor);
		// 에러 메시지 출력
		std::cout << "======================================" << endl;
		std::cout << "Invalid Card" << endl;
		// 세션이 종료되니 session_transac_history를 출력
		std::cout << "total transaction in this ATM session : \n" + session_transac_history;
		std::cout << "Closing ATM Session." << endl;
		std::cout << "======================================" << endl;
		called_session_num += 1;
	}
	// password가 틀렸을 시
	catch (Invalid_password) {
		// session_transac_history에 기록할 메시지 작성해서 기록
		session_transac_history += "Session Terminated : Invalid Password\n";
		session_transac_history_kor += "세션 종료 : 비밀번호 다름\n";
		// Session이 종료되었으니 Atm의 transac_history에 session_transac_history를 기록
		write_Transac_history(session_transac_history, session_transac_history_kor);
		card_account->transaction_Add("Session Terminated : Invalid Password\n", "세션 종료 : 비밀번호 다름\n");
		// 에러 메시지 출력
		std::cout << "======================================" << endl;
		std::cout << "Invalid Password" << endl;
		// 세션이 종료되니 session_transac_history를 출력
		std::cout << "total transaction in this ATM session : \n" + session_transac_history;
		std::cout << "Closing ATM Session." << endl;
		std::cout << "======================================" << endl;
		called_session_num += 1;
	}
}

void Atm_MultiBank::session_Main_Kor(Card* c) {
	std::cout << "======================================" << endl;
	std::cout << primary_bank->bank_Name() + " ATM 이용을 환영합니다." << endl;
	std::cout << "======================================" << endl;
	// session에서 이루어지는 모든 거래를 추적해서 기록하는 string을 하나 만든다.
	string session_transac_history = "Session : " + to_string(called_session_num) + "\n";
	string session_transac_history_kor = "세션 : " + to_string(called_session_num) + "\n";
	// account transaction에 더할 거래기록 저장공간
	string session_transac_accountSave = ">> Transactin history in " + primary_bank->bank_Name() + " ATM " + to_string(atm_serial) + "\n";
	string session_transac_accountSave_kor = primary_bank->bank_Name() + " ATM " + to_string(atm_serial) + " 에서 일어난 거래기록\n";
	// 들어온 카드의 Account pointer를 담는 곳
	Account* card_account = nullptr;
	// 출금한 횟수를 저장하는 곳
	int withdrawal_indicator = 0;
	try {
		// 들어온 카드의 Account pointer를 파악해서 card_account에 넣어야 한다. 만약 없는 Account면 그대로 session을 종료한다.
		Account* temp_account = primary_bank->search_myAccount(c->account_Num());
		if (temp_account == primary_bank->ret_zeroAccount()) {
			temp_account = primary_bank->search_anotherAccount(c->account_Num());
			if (temp_account == primary_bank->ret_zeroAccount()) {
				throw Invalid_account();
			}
			else {
				card_account = temp_account;
			}
		}
		else {
			card_account = temp_account;
		}

		session_transac_history += card_account->account_Num() + "'s transaction history\n";
		session_transac_history_kor += card_account->account_Num() + "의 거래기록\n";

		card_account->transaction_Add(session_transac_accountSave, session_transac_accountSave_kor);

		// 계좌의 비밀번호를 물어본다. 이때 true면 계속 진행하고 false면 예외처리
		bool temp_pw_valid = user_Authorize_Kor(card_account);
		if (temp_pw_valid == false) {
			throw Invalid_password();
		}

		// 드디어 실제로 거래를 처리하는 세션까지 왔다.
		do {
			int select_num = 0;
			std::cout << "======================================" << endl;
			std::cout << "원하는 거래를 선택하세요" << endl;
			std::cout << "1 : 입금" << endl;
			std::cout << "2 : 출금" << endl;
			std::cout << "3 : 송금" << endl;
			std::cout << "4 : 거래 기록" << endl;
			std::cout << "5 : 종료" << endl;
			std::cout << "======================================" << endl;
			cin >> select_num;
			try {
				// 잘못된 값이 들어오면 Cin_exception을 던진다. 
				if (cin.fail()) {
					throw Cin_exception();
				}
				if (select_num == 1) {
					int deal_money = Deposit_Kor(card_account);
					if (deal_money > 0) {
						// 거래가 끝난 후 거래 내역을 저장하는 곳
						string deposit_history = to_string(deal_money) + "Won added to " + card_account->account_Num() + "\n";
						string deposit_history_kor = to_string(deal_money) + "원이 " + card_account->account_Num() + "에 입금되었습니다." + "\n";
						session_transac_history += deposit_history;
						session_transac_history_kor += deposit_history_kor;
						card_account->transaction_Add(deposit_history, deposit_history_kor);
					}
					else if (deal_money == -1) {
						continue;
					}
				}
				else if (select_num == 2) {
					if (withdrawal_indicator > max_withdrawal) {
						std::cout << "======================================" << endl;
						std::cout << "세션당 출금할 수 있는 횟수를 초과했습니다." << endl;
						std::cout << "======================================" << endl;
					}
					else {
						int deal_money = Withdrawal_Kor(card_account);
						if (deal_money > 0) {
							withdrawal_indicator += 1;
							// 거래가 끝난 후 거래 내역을 저장하는 곳
							string withdrawal_history = to_string(deal_money) + "Won withdrawed from " + card_account->account_Num() + "\n";
							string withdrawal_history_kor = to_string(deal_money) + "원이 " + card_account->account_Num() + "에서 출금되었습니다." + "\n";
							session_transac_history += withdrawal_history;
							session_transac_history_kor += withdrawal_history_kor;
							card_account->transaction_Add(withdrawal_history, withdrawal_history_kor);
						}
						else if (deal_money == -1) {
							continue;
						}
					}
				}
				else if (select_num == 3) {
					// 보낼 계좌번호를 받는 부분
					string temp_sending_account = "";
					Account* temp_sending_accountptr = nullptr;
					do {
						std::cout << "======================================" << endl;
						std::cout << "송금할 계좌의 계좌번호를 입력하세요." << endl;
						std::cout << "======================================" << endl;
						cin >> temp_sending_account;
						try {
							// 계좌번호 자릿수가 맞지 않으면 다시 while문을 돌려야 한다.  
							if (temp_sending_account.length() != 14) {
								throw Invalid_account_num();
							}
							// 계좌번호의 pointer를 찾는다. 존재하지 않는다면 다시 while문을 돌려야 한다.
							temp_sending_accountptr = primary_bank->search_myAccount(temp_sending_account);
							if (temp_sending_accountptr == primary_bank->ret_zeroAccount()) {
								temp_sending_accountptr = primary_bank->search_anotherAccount(temp_sending_account);
								if (temp_sending_accountptr == primary_bank->ret_zeroAccount()) {
									throw Invalid_account();
								}
								else {
									// 실제로 다른 은행에 계좌번호가 존재하는 경우 : break
									break;
								}
							}
							else {
								// 실제로 자기 은행에 계좌번호가 존재하는 경우 : break
								break;
							}
						}
						catch (Invalid_account_num) {
							std::cout << "======================================" << endl;
							std::cout << "계좌번호 길이가 맞지 않습니다." << endl;
							std::cout << "======================================" << endl;
						}
						catch (Invalid_account) {
							std::cout << "======================================" << endl;
							std::cout << "계좌번호가 존재하지 않습니다." << endl;
							std::cout << "======================================" << endl;
						}
					} while (true);
					// 받은 계좌번호 포인터를 Transfer함수에 집어넣기
					int deal_money = Transfer_Kor(card_account, temp_sending_accountptr);
					if (deal_money > 0) {
						// 거래 내역을 기록한다.
						string transfer_history = to_string(deal_money) + "Won transfered from " + card_account->account_Num() + " to " + temp_sending_accountptr->account_Num() + "\n";
						string transfer_history_kor = to_string(deal_money) + "원이 " + card_account->account_Num() + " 에서 " + temp_sending_accountptr->account_Num() + "으로 송금되었습니다." + "\n";
						string transfer_history_account2 = "transfer from another account : " + transfer_history;
						string transfer_history_account2_kor = "다른 계좌에서 온 송금 : " + transfer_history_kor;
						session_transac_history += transfer_history;
						session_transac_history_kor += transfer_history_kor;
						card_account->transaction_Add(transfer_history, transfer_history_kor);
						temp_sending_accountptr->transaction_Add(transfer_history_account2, transfer_history_account2_kor);
					}
					else if (deal_money == -1) {
						continue;
					}
				}
				else if (select_num == 4) {
					std::cout << "======================================" << endl;
					std::cout << "계좌 은행 : " + card_account->account_Bank() << endl;
					std::cout << "계좌 주인 : " + card_account->account_User() << endl;
					std::cout << "계좌 번호 : " + card_account->account_Num() << endl;
					std::cout << "계좌 잔액 : " + to_string(card_account->account_Balance()) << endl;
					std::cout << "계좌 거래 기록은 다음과 같습니다. : " << endl;
					std::cout << card_account->ret_transac_history(false);
					std::cout << "======================================" << endl;
				}
				else if (select_num == 5) {
					break;
				}
				else {
					throw Num_exception();
				}
			}
			catch (Cin_exception) {
				// cin에 잘못된 자료형이 들어가면 cin의 버퍼를 지워줘야 다음 while문에서 cin를 사용시 infinite loop가 발생하지 않는다.
				std::cout << "======================================" << endl;
				std::cout << "문자가 아닌 숫자 1,2,3,4,5 중 하나를 입력하세요." << endl;
				std::cout << "======================================" << endl;
				// cin의 버퍼를 지워주는 부분
				cin.clear();
				cin.ignore(256, '\n');
			}
			catch (Num_exception) {
				std::cout << "======================================" << endl;
				std::cout << "숫자 1, 2, 3, 4, 5 중 하나를 입력하세요" << endl;
				std::cout << "======================================" << endl;
			}
		} while (true);

		// 그 모든 과정을 거치고서도 거래가 성공적으로 완료되었다는 뜻이니 Session을 종료한다. 
		write_Transac_history(session_transac_history, session_transac_history_kor);
		std::cout << "======================================" << endl;
		std::cout << "계좌 잔액 : " + to_string(card_account->account_Balance()) << endl;
		std::cout << "이번 ATM 세션에서 일어난 거래는 다음과 같습니다. : \n" + session_transac_history_kor;
		std::cout << "ATM 세션을 종료합니다." << endl;
		std::cout << "======================================" << endl;
		called_session_num += 1;
	}
	// Card에 있는 account가 없는 account일시 
	catch (Invalid_account) {
		// session_transac_history에 기록할 메시지 작성해서 기록
		session_transac_history += "Session Terminated : Account does not exist\n";
		session_transac_history_kor += "세션 종료 : 존재하지 않는 계좌\n";
		// Session이 종료되었으니 Atm의 transac_history에 session_transac_history를 기록
		write_Transac_history(session_transac_history, session_transac_history_kor);
		// 에러 메시지 출력
		std::cout << "======================================" << endl;
		std::cout << "유효하지 않은 카드입니다." << endl;
		// 세션이 종료되니 session_transac_history를 출력
		std::cout << "이번 ATM 세션에서 일어난 거래는 다음과 같습니다. : \n" + session_transac_history_kor;
		std::cout << "ATM 세션을 종료합니다." << endl;
		std::cout << "======================================" << endl;
		called_session_num += 1;
	}
	// password가 틀렸을 시
	catch (Invalid_password) {
		// session_transac_history에 기록할 메시지 작성해서 기록
		session_transac_history += "Session Terminated : Invalid Password\n";
		session_transac_history_kor += "세션 종료 : 비밀번호 다름\n";
		// Session이 종료되었으니 Atm의 transac_history에 session_transac_history를 기록
		write_Transac_history(session_transac_history, session_transac_history_kor);
		card_account->transaction_Add("Session Terminated : Invalid Password\n", "세션 종료 : 비밀번호 다름\n");
		// 에러 메시지 출력
		std::cout << "======================================" << endl;
		std::cout << "유효하지 않은 비밀번호입니다." << endl;
		// 세션이 종료되니 session_transac_history를 출력
		std::cout << "이번 ATM 세션에서 일어난 거래는 다음과 같습니다. : \n" + session_transac_history_kor;
		std::cout << "ATM 세션을 종료합니다." << endl;
		std::cout << "======================================" << endl;
		called_session_num += 1;
	}
}

void Atm_MultiBank::session_Admin(Card* c) {
	std::cout << "======================================" << endl;
	std::cout << "Welcome to " + primary_bank->bank_Name() + " ATM Admin Session." << endl;
	std::cout << "======================================" << endl;
	string session_transac_history = "Admin Session : " + to_string(called_session_num) + "\n";
	string session_transac_history_kor = "관리자 세션 : " + to_string(called_session_num) + "\n";
	// 바로 메뉴 하나를 보여준다. 
	try {
		if (c->bank_Name() != primary_bank->bank_Name()) {
			throw Primary_exception();
		}
		do {
			int select_num = 0;
			std::cout << "======================================" << endl;
			std::cout << primary_bank->bank_Name() + " ATM " + to_string(atm_serial) + " Admin Menu" << endl;
			std::cout << "Select the option you want to choose." << endl;
			std::cout << "1. Transaction History" << endl;
			std::cout << "2. Exit" << endl;
			std::cout << "======================================" << endl;
			cin >> select_num;
			try {
				if (cin.fail()) {
					throw Cin_exception();
				}
				if (select_num == 1) {
					// 거래기록 파일 내보내기
					ofstream fout;
					string output_filename = primary_bank->bank_Name() + " ATM " + to_string(atm_serial) + " transac_history_eng.txt";
					fout.open(output_filename);
					try {
						if (!fout) {
							throw File_open_fail();
						}
						fout << primary_bank->bank_Name() + " ATM " + to_string(atm_serial) + " transac_history\n";
						fout << transac_history;
						std::cout << "======================================" << endl;
						std::cout << "Transaction history output successed." << endl;
						std::cout << "======================================" << endl;
						fout.close();
					}
					catch (File_open_fail) {
						std::cout << "======================================" << endl;
						std::cout << "Transaction history output failed." << endl;
						std::cout << "======================================" << endl;
						fout.close();
					}
					// 거래기록 화면에 나타냄
					std::cout << "======================================" << endl;
					std::cout << "Transaction history of ATM : " << endl;
					std::cout << transac_history << endl;
					std::cout << "======================================" << endl;

					session_transac_history += "ATM transaction history viewed\n";
					session_transac_history_kor += "ATM 거래기록 조회됨\n";
				}
				else if (select_num == 2) {
					break;
				}
				else {
					throw Num_exception();
				}
			}
			catch (Cin_exception) {
				// cin에 잘못된 자료형이 들어가면 cin의 버퍼를 지워줘야 다음 while문에서 cin를 사용시 infinite loop가 발생하지 않는다.
				std::cout << "======================================" << endl;
				std::cout << "Input only number 1 or 2. Not Charactor." << endl;
				std::cout << "======================================" << endl;
				// cin의 버퍼를 지워주는 부분
				cin.clear();
				cin.ignore(256, '\n');
			}
			catch (Num_exception) {
				std::cout << "======================================" << endl;
				std::cout << "Input only number 1 or 2." << endl;
				std::cout << "======================================" << endl;
			}
		} while (true);
	}
	catch (Primary_exception) {
		std::cout << "======================================" << endl;
		cout << "Invalid Admin Card" << endl;
		std::cout << "======================================" << endl;
		session_transac_history += "Admin Session terminated : Invalid Admin Card used.\n";
		session_transac_history_kor += "관리자 세션 종료 : 유효하지 않은 관리자 카드가 사용되었습니다.\n";
	}
	// 세션이 종료됨.
	std::cout << "======================================" << endl;
	std::cout << "Closing ATM Session." << endl;
	std::cout << "======================================" << endl;
	write_Transac_history(session_transac_history, session_transac_history_kor);
	called_session_num += 1;
}

void Atm_MultiBank::session_Admin_Kor(Card* c) {
	std::cout << "======================================" << endl;
	std::cout << primary_bank->bank_Name() + " ATM 관리자 세션에 온 것을 환영합니다." << endl;
	std::cout << "======================================" << endl;
	string session_transac_history = "Admin Session : " + to_string(called_session_num) + "\n";
	string session_transac_history_kor = "관리자 세션 : " + to_string(called_session_num) + "\n";
	// 바로 메뉴 하나를 보여준다. 
	try {
		if (c->bank_Name() != primary_bank->bank_Name()) {
			throw Primary_exception();
		}
		do {
			int select_num = 0;
			std::cout << "======================================" << endl;
			std::cout << primary_bank->bank_Name() + " ATM " + to_string(atm_serial) + " 관리자 메뉴" << endl;
			std::cout << "원하는 메뉴를 선택하세요." << endl;
			std::cout << "1. 거래기록 열람" << endl;
			std::cout << "2. 종료" << endl;
			std::cout << "======================================" << endl;
			cin >> select_num;
			try {
				if (cin.fail()) {
					throw Cin_exception();
				}
				if (select_num == 1) {
					// 거래기록 파일 내보내기
					ofstream fout;
					string output_filename = primary_bank->bank_Name() + " ATM " + to_string(atm_serial) + " transac_history_kor.txt";
					fout.open(output_filename);
					try {
						if (!fout) {
							throw File_open_fail();
						}
						fout << primary_bank->bank_Name() + " ATM " + to_string(atm_serial) + " transac_history\n";
						fout << transac_history_kor;
						std::cout << "======================================" << endl;
						std::cout << "거래 기록 출력에 성공했습니다." << endl;
						std::cout << "======================================" << endl;
						fout.close();
					}
					catch (File_open_fail) {
						std::cout << "======================================" << endl;
						std::cout << "거래 기록 출력에 실패했습니다." << endl;
						std::cout << "======================================" << endl;
						fout.close();
					}
					std::cout << "======================================" << endl;
					std::cout << "ATM에서 일어난 거래는 다음과 같습니다 : " << endl;
					std::cout << transac_history_kor << endl;
					std::cout << "======================================" << endl;
					session_transac_history += "ATM transaction history viewed\n";
					session_transac_history_kor += "ATM 거래기록 조회됨\n";
				}
				else if (select_num == 2) {
					break;
				}
				else {
					throw Num_exception();
				}
			}
			catch (Cin_exception) {
				// cin에 잘못된 자료형이 들어가면 cin의 버퍼를 지워줘야 다음 while문에서 cin를 사용시 infinite loop가 발생하지 않는다.
				std::cout << "======================================" << endl;
				std::cout << "문자 외에 숫자 1 또는 2를 입력하세요." << endl;
				std::cout << "======================================" << endl;
				// cin의 버퍼를 지워주는 부분
				cin.clear();
				cin.ignore(256, '\n');
			}
			catch (Num_exception) {
				std::cout << "======================================" << endl;
				std::cout << "숫자 1 또는 2를 입력하세요." << endl;
				std::cout << "======================================" << endl;
			}
		} while (true);
	}
	catch (Primary_exception) {
		std::cout << "======================================" << endl;
		cout << "유효하지 않은 관리자 카드입니다." << endl;
		std::cout << "======================================" << endl;
		session_transac_history += "Admin Session terminated : Invalid Admin Card used.\n";
		session_transac_history_kor += "관리자 세션 종료 : 유효하지 않은 관리자 카드가 사용되었습니다.\n";
	}
	// 세션이 종료됨.
	std::cout << "======================================" << endl;
	std::cout << "ATM 세션을 종료합니다." << endl;
	std::cout << "======================================" << endl;
	write_Transac_history(session_transac_history, session_transac_history_kor);
	called_session_num += 1;
}


// test case를 대입해 반영되는 항목별로 테스트해보는 곳
int main() {
	// sample demo case 구현부
	Bank* Kakao = new Bank("Kakao");
	Bank* Daegu = new Bank("Daegu");
	Kakao->add_Bank(Daegu);
	Daegu->add_Bank(Kakao);

	Card* card_David = Kakao->create_Account("111-111-111111", "David", 5000, 2022);
	Card* card_Jane = Daegu->create_Account("222-222-222222", "Jane", 5000, 2022);
	Card* card_Kate = Kakao->create_Account("333-333-333333", "Kate", 5000, 2022);

	Card* card_Admin_Kakao = Kakao->create_Admin();
	Card* card_Admin_Daegu = Daegu->create_Admin();

	int atm_1_initial_cash[4] = { 5,0,0,0 };
	Atm* ATM_1 = new Atm_SingleBank(111111, Kakao, true, atm_1_initial_cash);

	int atm_2_initial_cash[4] = { 5,0,0,0 };
	Atm* ATM_2 = new Atm_MultiBank(222222, Daegu, false, atm_2_initial_cash);
	
	int atm_3_initial_cash[4] = { 5,0,0,0 };
	Atm* ATM_3 = new Atm_MultiBank(333333, Daegu, false, atm_3_initial_cash);

	// primary test
	ATM_1->session_Start(card_Jane);

	// password test
	ATM_1->session_Start(card_David);

	// Singlebank test
	ATM_1->session_Start(card_David);
	// test 후 잔액 표시
	Kakao->print_account_Remainbalance();
	Daegu->print_account_Remainbalance();
	ATM_1->print_Leftcash();
	ATM_2->print_Leftcash();
	ATM_3->print_Leftcash();

	// Multibank test
	ATM_2->session_Start(card_David);
	// test 후 잔액 표시
	Kakao->print_account_Remainbalance();
	Daegu->print_account_Remainbalance();
	ATM_1->print_Leftcash();
	ATM_2->print_Leftcash();
	ATM_3->print_Leftcash();

	// admin test
	ATM_1->session_Start(card_Admin_Kakao);
	ATM_2->session_Start(card_Admin_Daegu);

	delete card_David;
	delete card_Jane;
	delete card_Kate;
	delete ATM_1;
	delete ATM_2;
	delete ATM_3;
	delete Kakao;
	delete Daegu;
}