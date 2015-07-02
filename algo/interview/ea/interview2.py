#!/usr/bin/env python

import sys

class User(object):
    def __init__(self, name):
        self.name = name
        self.balance = 0

class BankSystemException(Exception):
    def __init__(self, name):
        self.name = name

class UserAlreadyExist(BankSystemException):
    pass

class UserNotExist(BankSystemException):
    pass

class NotSufficientMoney(BankSystemException):
    pass

class BalanceExceed(BankSystemException):
    pass

class PayeeNotFound(BankSystemException):
    def __init__(self, name, payee):
        self.name = name
        self.payee = payee

# System Singleton.
class System(object):
    users = {}
    payees = {}
    max_balance = 2000000
    @classmethod
    def addUser(cls, name):
        if (cls.users.has_key(name)):
            raise UserAlreadyExist(name)
        else:
            cls.users[name] = User(name)
        return "%s added" % name
    @classmethod
    def delUser(cls, name):
        if (cls.users.has_key(name)):
            # if in payees, delete it
            for _, host_payees in cls.payees.iteritems():
                if name in host_payees:
                    host_payees.remove(name)
            del cls.users[name]
        else:
            raise UserNotExist(name)

        return "%s deleted" % name

    @classmethod
    def debit(cls, name, count):
        user = cls.getUser(name)
        if (user.balance < count):
            raise NotSufficientMoney(name)
        else:
            user.balance -= count
        return "%s's account debited %s successfully!!" % (name, count)

    @classmethod
    def credit(cls, name, count):
        user = cls.getUser(name)
        if (user.balance + count > cls.max_balance):
            raise BalanceExceed(name)
        else:
            user.balance += count
        return "%s's account credited %s successfully!!" % (name, count)

    @classmethod
    def addPayee(cls, name, payee_name):
        me = cls.getUser(name)
        cls.getUser(payee_name) # just to check whether payee exists
        if (cls.payees.has_key(name)):
            me.add(payee_name)
        else:
            cls.payees[name] = set(payee_name)
        return "Added payee successfully!!"
        
    @classmethod
    def getUser(cls, name):
        if (not cls.users.has_key(name)):
            raise UserNotExist(name)
        else:
            return cls.users[name]

    @classmethod
    def transfer(cls, sender_name, receiver_name, count):
        # TODO: Since our system has only one thread, we don't need to
        # add special processing for this part
        # Otherwise, we may need to add transaction, lock to protect this
        # piece of code.
        cls.getUser(sender_name) # check user existence
        if receiver_name in cls.payees.get(sender_name, set()):
            cls.getUser(receiver_name) # check user existence
            cls.debit(sender_name, count)
            cls.credit(receiver_name, count)
        else:
            raise PayeeNotFound(sender_name, receiver_name)
        return "Transfer successfull!!"

    @classmethod
    def listByName(cls):
        return sorted(cls.users.keys(), key=lambda n:n)
    
    @classmethod
    def listByBalance(cls):
        return [user.name for user in sorted(cls.users.values(), key=lambda user:user.balance, reverse=True)]


def parseAddUser(line):
    _, name = line.split()
    return [name]

def parseDelUser(line):
    _, name = line.split()
    return [name]

def parseDebit(line):
    _, name, count = line.split()
    return [name, int(count)]

def parseCredit(line):
    _, name, count = line.split()
    return [name, int(count)]

def parseAddPayee(line):
    _, name, payee = line.split()
    return [name, payee]

def parseTransfer(line):
    _, sender, receiver, count = line.split()
    return [sender, receiver, int(count)]

def parseList(line):
    return []

def parseListBalance(line):
    return []


# combine operator.
# this function combines all the funcitons which is passed as arguments
def combine(*fns):
    def wrapper(arg):
        for f in reversed(fns):
            arg = f(arg)
        return arg
    return wrapper

action_dispatch = {
        "AddUser": combine(lambda args:System.addUser(*args), parseAddUser),
        "DeleteUser": combine(lambda args:System.delUser(*args), parseDelUser),
        "Debit": combine(lambda args:System.debit(*args), parseDebit),
        "Credit": combine(lambda args:System.credit(*args), parseCredit),
        "Transfer": combine(lambda args:System.transfer(*args), parseTransfer),
        "AddPayee": combine(lambda args:System.addPayee(*args), parseAddPayee),
        "List": combine(lambda args:System.listByName(*args), parseList),
        "List balance": combine(lambda args:System.listByBalance(*args), parseListBalance)
        }

# parse the line and dispatch to the right method according to the given action
def parseAndDispatch(line):
    tokens = line.split()
    action_name = ""
    if tokens[0] == 'List' and len(tokens) >= 2 and tokens[1] == 'balance':
        action_name = "List balance"
    else:
        action_name = tokens[0]
    return action_dispatch[action_name](line)

def main():
    for line in sys.stdin:
        line = line.strip()
        if line:
            try:
                res = parseAndDispatch(line)
                print res
            except UserNotExist as e:
                print "Error: invalid user", e.name
            except UserAlreadyExist as e:
                print "Error:", e.name, "already exist"
            except NotSufficientMoney as e:
                print "Error:", e.name, "doesn't have sufficient money for action:", line
            except BalanceExceed as e:
                print "Error:", e.name, "'s deposit exceeds max balance"
            except PayeeNotFound as e:
                print "Error:", e.payee, "'s not in the payee list of", e.name
            except: 
                raise

if __name__ == '__main__':
    main()
