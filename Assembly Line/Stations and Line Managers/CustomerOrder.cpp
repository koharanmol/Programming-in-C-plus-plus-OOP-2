/***************************************
Name: Anmol Singh
Id: 147528178
Assignment: Project - Milestone 3
Date: 5 April 2019
****************************************/

#include "CustomerOrder.h"

namespace sict {
	//default constructor 
	//
	CustomerOrder::CustomerOrder() {}

	// exact the value from the given strings
	//
	CustomerOrder::CustomerOrder(const std::string& src) {
		size_t next{ 0 };
		customer = utilities.extractToken(src, next);
		if (customer.size() > utilities.getFieldWidth()) {
			utilities.setFieldWidth(customer.size());
		}
		if (next <= src.size()) {
			product = utilities.extractToken(src, next);
		}
		while (next <= src.size()) {
			ItemInfo* temp;
			temp = new ItemInfo[count];
			for (size_t i = 0; i < count; i++) { temp[i] = items[i]; }
			delete[] items;
			items = new ItemInfo[++count];
			for (size_t i = 0; i < count - 1; i++) { items[i] = temp[i]; }
			delete[] temp;
			items[count - 1].item = utilities.extractToken(src, next);
		}
	}

	//Move constructor 
	//
	CustomerOrder::CustomerOrder(CustomerOrder&& src) {
		if (this != &src) {
			*this = std::move(src);
		}
	}

	//Destructor 
	//
	CustomerOrder::~CustomerOrder() { 
		delete[]items;
	}

	// fills the orders by requirement
	//
	void CustomerOrder::fillItem(ItemSet& item, std::ostream& os) {
		for (size_t i = 0; i < count; i++) {
			if (item.getName() == items[i].item) {
				if (item.getQuantity() > 0 && items[i].isValid == false) {
					items[i].isValid = true;
					items[i].Serial = item.getSerialNumber();
					if (item.getQuantity() > 0) --item;
					os << " Filled " << customer << " [" << product << "][" << items[i].item << "][" << items[i].Serial << ']' << std::endl;;
				}
				else if (item.getQuantity() > 0 && items[i].isValid) {
					os << " Unable to fill " << customer << " [" << product << "][" << items[i].item << "][" << items[i].Serial << "] already filled" << std::endl;;
				}
				else {
					os << " Unable to fill " << customer << " [" << product << "][" << items[i].item << "][" << items[i].Serial << "] out of stock" << std::endl;
				}
			}
		}
	}

	// return the bool value if there is product, using and gate logic
	//
	bool CustomerOrder::isFilled() const {
		int valid{ 1 };
		for (size_t i = 0; i < count; i++) {
			valid *= static_cast<int>(items[i].isValid);
		}
		return static_cast<bool>(valid);
	}

	//returns boolean value regarding its status, using and gate logic
	//
	bool CustomerOrder::isItemFilled(const std::string& item) const {
		int valid{ 1 };
		for (size_t i = 0; i < count; i++) {
			if (items[i].item == item) {
				valid *= static_cast<int>(items[i].isValid);
			}
		}
		return static_cast<bool>(valid);
	}

	//returns the name 
	//
	std::string CustomerOrder::getNameProduct() const {
		std::string nameProduct = customer + " [" + product + ']';
		return nameProduct;
	}

	// display function to display the content
	//
	void CustomerOrder::display(std::ostream& os, bool showDetail) const {
		if (!showDetail) {
			os.width(utilities.getFieldWidth());
			os << customer;
			os << " [" << product << ']' << std::endl;
			if (count > 0) {
				for (size_t i = 0; i < count; i++) {
					for (size_t i = 0; i < utilities.getFieldWidth() + 1; i++) { os << ' '; }
					os << items[i].item << std::endl;
				}
			}
		}
		else {
			os.width(utilities.getFieldWidth());
			os << customer;
			os << " [" << product << ']' << std::endl;
			if (count > 0) {
				for (size_t i = 0; i < count; i++) {
					for (size_t i = 0; i < utilities.getFieldWidth() + 1; i++) { os << ' '; }
					os << '[' << items[i].Serial << "] " << items[i].item;
					os << " - " << (items[i].isValid ? "FILLED" : "MISSING") << std::endl;
				}
			}
		}
	}

	//Move assignment operator 
	//
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) {
		if (this != &src) {
			delete[] items;
			items = nullptr;
			customer = src.customer;
			product = src.product;
			count = src.count;
			items = src.items;
			src.customer = "";
			src.product = "";
			src.count = 0;
			src.items = nullptr;
		}
		return *this;
	}


}