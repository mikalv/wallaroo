#ifndef __ARIZONA_STATE_HPP__
#define __ARIZONA_STATE_HPP__

#include <string>
#include <map>

using std::string;
using std::map;

// forward declaration
class Account;

enum Side
{
  Buy = 0,
  Sell = 1
};

class Proceeds
{
private:
  double _proceeds_short;
  double _proceeds_long;
  double _open_short;
  double _open_long;
  string _isin_id;
public:
  Proceeds(double proceeds_short_, double proceeds_long_, double open_short_, double open_long_, string isin_id_);
  double proceeds_short() { return _proceeds_short; }
  double proceeds_long() { return _proceeds_long; }
  double open_short() { return _open_short; }
  double open_long() { return _open_long; }
  string isin() { return _isin_id; }
  Proceeds& add(Proceeds& that);
  bool operator==(Proceeds& that);
};

class Order
{
private:
  string _order_id;
  Side _side;
  uint32_t _quantity;
  double _price;
public:
  Order(string& order_id_, Side side_, uint32_t quantity_, double price_);
  bool operator==(Order& that);
  Proceeds proceeds();
};

class Orders
{
private:
  map<string, Order *> _orders;
public:
  Orders();
  ~Orders();
  void add_order(string& order_id, Side side_, uint32_t quantity, double price_);
  void cancel_order(string& order_id);
  Proceeds proceeds();
  Proceeds proceeds_without_order(string& order_id_);
  size_t count() { return _orders.size(); }
};

class ISIN
{
private:
  string _isin_id;
  Orders _orders;
public:
  ISIN(string& isin_id_);
  void add_order(string& _order_id_, Side side_, double quantity_, double price_, Account *account_);
  void cancel_order(string& _order_id_);
  Proceeds proceeds();
  Proceeds proceeds_without_order(string& order_id_);
};

class ISINs
{
private:
  map<string, ISIN*> _isins;
  ISIN* _add_isin(string& isin_id_);
  ISIN* _isin_by_isin_id(string& isin_id_);
public:
  ISINs();
  ~ISINs();
  void add_order(string& isin_id_, string& order_id_, Side side_, uint32_t quantity_, double price_, Account *account_);
  void cancel_order(string& isin_id_, string& order_id_);
  Proceeds proceeds_for_isin(string& isin_id_);
  Proceeds proceeds_for_isin_without_order(string& isin_id_, string& order_id_);
  Proceeds proceeds_with_order(string& isin_id_, string& order_id_, Side side_, uint32_t quantity_, double price_);
  Proceeds proceeds_with_cancel(string& isin_id_, string& order_id_);
};

class Account
{
private:
  string _account_id;
  ISINs _isins;
  map<string, string> _order_id_to_isin_id;
public:
  Account(string& account_id_);
  void add_order(string& isin_id_, string& order_id_, Side side_, uint32_t quantity_, double price_);
  void cancel_order(string& isin_id_, string& order_id_);
  void cancel_order(string& order_id_);
  Proceeds proceeds_for_isin(string& isin_id_);
  Proceeds proceeds_with_order(string& isin_id_, string& order_id_, Side side_, uint32_t quantity_, double price_);
  Proceeds proceeds_with_cancel(string& isin_id_, string& order_id_);
  Proceeds proceeds_with_cancel(string& order_id_);
  void associate_order_id_to_isin_id(string& order_id_, string& isin_id_);
  void disassociate_order_id_to_isin_id(string& order_id_, string& isin_id_);
};

class Accounts
{
private:
  map<string, Account *> _accounts;
  Account *_account_by_account_id(string& account_id_);
  Account *_add_account(string& account_id_);
public:
  Accounts();
  ~Accounts();
  void add_order(string& account_id_, string& isin_id_, string& order_id_, Side side_, uint32_t quantity_, double price_);
  void cancel_order(string& account_id_, string& order_id_);
  Proceeds proceeds_for_isin(string& account_id_, string& isin_id_);
  Proceeds proceeds_with_order(string& account_id_, string& isin_id_, string& order_id_, Side side_, uint32_t quantity_, double price_);
  Proceeds proceeds_with_cancel(string& account_id_, string& order_id_);
};

class Client
{
private:
  Accounts _accounts;
  string _client_id;
public:
  Client(string& client_id_);
  void add_order(string& account_id_, string& isin_id_, string& order_id_, Side side_, uint32_t quantity_, double price_);
  void cancel_order(string& account_id_, string& order_id_);
  Proceeds proceeds_for_isin(string& account_id_, string& isin_id_);
  Proceeds proceeds_with_order(string& account_id_, string& isin_id_, string& order_id_, Side side_, uint32_t quantity_, double price_);
  Proceeds proceeds_with_cancel(string& account_id_, string& order_id_);
};

class Clients
{
private:
  map<string, Client*> _clients;
  Client *_client_by_client_id(string& client_id_);
  Client *_add_client(string& client_id_);
public:
  Clients();
  ~Clients();
  void add_order(string& client_id_, string& account_id_, string& isin_id_, string& order_id_, Side side_, uint32_t quantity_, double price_);
  void cancel_order(string& client_id_, string& isin_id_, string& order_id_);
  Proceeds proceeds_for_isin(string& client_id, string& account_id_, string& isin_id_);
  Proceeds proceeds_with_order(string& client_id_, string& account_id_, string& isin_id_, string& order_id_, Side side_, uint32_t quantity_, double price_);
  Proceeds proceeds_with_cancel(string& client_id_, string& account_id_, string& order_id_);
};

#endif // __ARIZONA_STATE_HPP__
