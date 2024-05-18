#ifndef CLIENTCONSOLEFAKE_H
#define CLIENTCONSOLEFAKE_H

#include <iostream>

#include "Client.h"

class ClientConsoleFake : public Client
{
public:
	ClientConsoleFake() { }
	virtual ~ClientConsoleFake() { }

	virtual int connect(const std::string& addr)
	{
		std::cout << "client sends connect request to " << addr << std::endl; 
		return 0;
	}

	virtual void disconnect()
	{
		std::cout << "client sends disconnect request" << std::endl; 
	}

	virtual int publish(const std::string& topic, const std::string& data)
	{
		std::cout << "client publishes topic: " << topic << ", data: " << data
			<< std::endl;
		return 0;
	}

	virtual int subscribe(const std::string& topic)
	{
		std::cout << "client subscribes to topic: " << topic << std::endl;
		return 0;
	}

	virtual int unsubscribe(const std::string& topic)
	{
		std::cout << "client unsubscribes from topic: " << topic << std::endl;
		return 0;
	}


private:

};

#endif /* CLIENTCONSOLEFAKE_H */

