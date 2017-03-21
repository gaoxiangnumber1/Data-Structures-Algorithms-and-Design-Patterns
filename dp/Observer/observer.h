#ifndef OBSERVER_H
#define OBSERVER_H
#include <list>
#include <iostream>
using namespace std;
typedef int State;

class Observer;

class Subject
{
private:
	list<Observer *> observers_;

public:
	Subject()
	{
		cout << "##########Constructor: Subject\n";
	}
	virtual ~Subject();
	virtual void Attach(Observer *observer);
	virtual void Detach(Observer *observer);
	virtual void Notify();
	virtual void SetState(const State state) = 0;
	virtual State GetState() = 0;
};

class ConcreteSubject : public Subject
{
private:
	State state_;

public:
	ConcreteSubject() : state_(-1)
	{
		cout << "##########Constructor: ConcreteSubject\n";
	}
	~ConcreteSubject()
	{
		cout << "~~~~~~~~~~Destructor: ConcreteSubject\n";
	}
	void SetState(State state);
	State GetState();
};

class Observer
{
public:
	Observer()
	{
		cout << "##########Constructor: Observer\n";
	}
	virtual ~Observer()
	{
		cout << "~~~~~~~~~~Destructor: Observer\n";
	}
	virtual void Update(Subject *subject) = 0;
	virtual Subject *&GetSubject() = 0;
};

class ConcreteObserver : public Observer
{
private:
	Subject *subject_;

public:
	ConcreteObserver(Subject *subject);
	~ConcreteObserver();
	void Update(Subject *subject);
	Subject *&GetSubject();
};

#endif // OBSERVER_H
