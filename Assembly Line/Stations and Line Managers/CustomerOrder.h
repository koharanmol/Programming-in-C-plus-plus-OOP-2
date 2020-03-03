/***************************************
Name: Anmol Singh
Id: 147528178
Assignment: Project - Milestone 2
Date: 5 April 2019
****************************************/

#ifndef SICT_CUSTOMERORDER_H_
#define SICT_CUSTOMERORDER_H_
#include <iostream>
#include "ItemSet.h"
#include "Utilities.h"

namespace sict {
	struct ItemInfo;

	class CustomerOrder {
		std::string customer{};
		std::string product{};
		ItemInfo* items = nullptr;
		size_t count{ 0 };
		Utilities utilities;
	public:
		CustomerOrder();
		CustomerOrder(const std::string&);
		CustomerOrder(CustomerOrder&) = delete;
		CustomerOrder(CustomerOrder&&);
		~CustomerOrder();
		void fillItem(ItemSet& item, std::ostream& os);
		bool isFilled() const;
		bool isItemFilled(const std::string& item) const;
		std::string getNameProduct() const;
		void display(std::ostream& os, bool showDetail = false) const;
		CustomerOrder& operator=(CustomerOrder&) = delete;
		CustomerOrder& operator=(CustomerOrder&&);
	};

	struct ItemInfo {
		std::string item{};
		unsigned int Serial{ 0 };
		bool isValid{ false };
	};

}



#endif // !SICT_CUSTOMERORDER_H_
