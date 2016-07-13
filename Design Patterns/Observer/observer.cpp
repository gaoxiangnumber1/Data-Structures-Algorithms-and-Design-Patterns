#include "observer.h"
#include <algorithm>

/* Subject */
Subject::~Subject()
{
	list<Observer *>::iterator it = observers_.begin(), temp;
	while(it != observers_.end())
	{
		temp = it++;
		delete(*temp);
	}
	observers_.clear();
	cout << "~~~~~~~~~~Destructor: Subject\n";
}

void Subject::Attach(Observer *observer)
{
	observers_.push_back(observer);
	observer->GetSubject() = this;
	cout << "Attach an observer.\n";
}

void Subject::Detach(Observer *observer)
{
	list<Observer *>::iterator it = find(observers_.begin(), observers_.end(), observer);
	if(it != observers_.end() && (*it) != NULL)
	{
		(*it)->GetSubject() = NULL;
		observers_.erase(it);
	}
	cout << "Detach an observer.\n";
}

void Subject::Notify()
{
	cout << "**************Notify observers Begin**************\n";
	list<Observer *>::iterator it = observers_.begin();
	for(; it != observers_.end(); ++it)
	{
		(*it)->Update(this);
	}
	cout << "**************Notify observers End**************\n";
}

/* ConcreteSubject */

void ConcreteSubject::SetState(State state)
{
	cout << "SetState by ConcreteSubject\n";
	state_ = state;
}

State ConcreteSubject::GetState()
{
	cout << "GetState by ConcreteSubject\n";
	return state_;
}

/* ConcreteObserver */

ConcreteObserver::ConcreteObserver(Subject *subject)
{
	subject_ = subject;
	subject_->Attach(this);
	cout << "##########Constructor: ConcreteObserver\n";
}

ConcreteObserver::~ConcreteObserver()
{
	if(subject_)
	{
		subject_->Detach(this);
		subject_ = NULL;
		// delete subject_; is WRONG!
		// There may be other observers still observe your subject.
	}
	cout << "~~~~~~~~~~Destructor: ConcreteObserver\n";
}

void ConcreteObserver::Update(Subject *subject)
{
	if(subject)
	{
		cout << "The observer state is " << subject->GetState() << "\n";
	}
}

Subject *&ConcreteObserver::GetSubject()
{
	cout << "GetSubject by ConcreteObserver\n";
	return subject_;
}

