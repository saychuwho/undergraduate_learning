# console ATM

This project is what me and other two students made during term project of Objective Oriented Programming class in DGIST at 2022 2nd semester. 

It demonstrates ATM machine's behavior based on console input and output

I contributed basic structure (like what class should be made), and member functions that represent session of atm(Session_Start(), Session_Main(), etc.)

Source code of this project is might long. This is because we have to submit the code in one file so we do not divided code with several cpp and header files.

## ATM's behavior
### Basic attribute
- Deposit (cash, check)
- Withdrawal (cash only)
- Transfer (cash, check, account)
- read transaction history
- admin menu / show the whole transaction history of ATM
### Types of ATM
- Singlebank ATM(ATM only accepts accounts from primary bank)
- Multibank ATM(ATM allows all verified accounts)
- UniLingual ATM(ATM only displays English)
- MultiLingual ATM(ATM can display English and Korean)
## How to start
These setting's should be done inside main()

1. Set the Bank

Set the Bank like this. And add the another Bank's address with add_Bank().
<pre>
<code>
Bank* Kakao = new Bank("Kakao");
Bank* Daegu = new Bank("Daegu");
Kakao->add_Bank(Daegu);
Daegu->add_Bank(Kakao);
</code>
</pre>
2. Set the Account

Make the account with Bank class's create_Account(). create_Account requires account number(string), account user(string), account initial balance(int), password(int). If you need Admin card, make admin card with Bank class's create_Admin()

<pre>
<code>
// Make the account
Card* card_David = Kakao->create_Account("111-111-111111", "David", 5000, 2022);
Card* card_Jane = Daegu->create_Account("222-222-222222", "Jane", 5000, 2022);
Card* card_Kate = Kakao->create_Account("333-333-333333", "Kate", 5000, 2022);
// Make the admin card
Card* card_Admin_Kakao = Kakao->create_Admin();
Card* card_Admin_Daegu = Daegu->create_Admin();
</code>
</pre>

3. Set the ATM

ATM needs initial cash. initial cash is made with int array. From front of the array, each number inside the array indicates 1,000 won, 5,000 won, 10,000 won, 50,000 won.

ATM is made with each type of ATM's constructor. If ATM is singlebank ATM, ATM is made with Atm_SingleBank class's constructor. Both singlebank and multibank constructor needs serial number(int), primary bank(Bank pointer), Unilingual indicator(bool), and initial cash(int array)

<pre>
<code>
int atm_1_initial_cash[4] = { 5,0,0,0 };
Atm* ATM_1 = new Atm_SingleBank(111111, Kakao, true, atm_1_initial_cash);

int atm_2_initial_cash[4] = { 5,0,0,0 };
Atm* ATM_2 = new Atm_MultiBank(222222, Daegu, false, atm_2_initial_cash);
</code>
</pre>

4. Start the session

Session starts with ATM's member function session_Start(). session_Stat() requires Card pointer.

If you put admin card's pointer, ATM will start with admin session.
<pre>
<code>
ATM_1->session_Start(card_Jane);
</code>
</pre>
