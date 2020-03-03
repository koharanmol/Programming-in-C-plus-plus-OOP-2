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

	//exacts the values from the string
	//
	CustomerOrder::CustomerOrder(const std::string& sourceStr) {
		size_t next_pos{ 0 };
		customer = utilities.extractToken(sourceStr, next_pos);
		if (customer.size() > utilities.getFieldWidth()) {
			utilities.setFieldWidth(customer.size());
		}
		if (next_pos <= sourceStr.size()) {
			product = utilities.extractToken(sourceStr, next_pos);
		}
		while (next_pos <= sourceStr.size()) {
			ItemInfo* temp;
			temp = new ItemInfo[count];
			for (size_t i = 0; i < count; i++) { temp[i] = items[i]; }
			delete[] items;
			items = new ItemInfo[++count];
			for (size_t i = 0; i < count - 1; i++) { items[i] = temp[i]; }
			delete[] temp;
			items[count - 1].item = utilities.extractToken(sourceStr, next_pos);
		}
	}

	//Move constructor 
	CustomerOrder::CustomerOrder(CustomerOrder&& src) {
		if (this != &src) { 
			*this = std::move(src);
		}
	}

	//Destructor
	CustomerOrder::~CustomerOrder() {
		delete[]items;
	}

	// fill the customer and product
	//
	void CustomerOrder::fillItem(ItemSet& item, std::ostream& os) {
		for (size_t i = 0; i < count; i++) {
			if (item.getName() == items[i].item) {
				if (item.getQuantity() > 0 && items[i].Valid == false) {
					items[i].Valid = true;
					items[i].SerialNumber = item.getSerialNumber();
					if (item.getQuantity() > 0) --item;
					os << " Filled " << customer << " [" << product << "][" << items[i].item << "][" << items[i].SerialNumber << ']' << std::endl;;
				}
				else if (item.getQuantity() > 0 && items[i].Valid) {
					os << " Unable to fill " << customer << " [" << product << "][" << items[i].item << "][" << items[i].SerialNumber << "] already filled" << std::endl;;
				}
				else {
					os << " Unable to fill " << customer << " [" << product << "][" << items[i].item << "][" << items[i].SerialNumber << "] out of stock" << std::endl;
				}
			}
		}
	}

	//returns boolean value of whether all the orders are filled
	//
	bool CustomerOrder::isFilled() const {
		int valid= true;
		for (size_t i = 0; i < count; i++) {
			valid = items[i].Valid;
		}
		return valid;
	}

	// return true if matches the request
	//
	bool CustomerOrder::isItemFilled(const std::string& item) const {
		int valid = true;
		for (size_t i = 0; i < count; i++) {
			if (items[i].item == item) {
				valid = items[i].Valid;
			}
		}
		return valid;
	}

	//returns the name 
	//
	std::string CustomerOrder::getNameProduct() const {
		std::string nameProduct = customer + " [" + product + ']';
		return nameProduct;
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

	//displays function
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
					os << '[' << items[i].SerialNumber << "] " << items[i].item;
					os << " - " << (items[i].Valid ? "FILLED" : "MISSING") << std::endl;
				}
			}
		}
	}

	


}