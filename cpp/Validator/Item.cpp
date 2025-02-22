#include "Item.h"

namespace validator {



	Item::Item(const int id, const int customer_id, const bool rotated, const ItemType& type) {
		this->id = id;
		this->customer_id = customer_id;
		this->rotated = rotated;
		this->type_id = type.id;
		this->l = type.l;
		this->w = type.w;
		this->h = type.h;
		this->mass = type.mass;
		this->fragility = type.fragility;
		this->lbs = type.lbs;
		min = Point(0, 0, 0);
		max = Point(0, 0, 0);
		this->support = 0;
		this->sumLoad = 0.0;
		this->load = std::vector<double>(this->l * this->w, 0);
	}

	Item::Item() {
		min = max = Point(0, 0, 0);
		id = customer_id = l = w = h = mass = type_id = fragility = lbs = support = sumLoad = 0;
	}


	void Item::setPosition(Point point) {
		min = point;
		unsigned int maxX = !rotated ? min.x + l : min.x + w;
		unsigned int maxY = !rotated ? min.y + w : min.y + l;
		unsigned int maxZ = min.z + h;
		max = Point(maxX, maxY, maxZ);
	}

	bool Item::isBelow(Item& other, const bool touch) const {
		if (this->id == other.id) return false;
		
		return (((touch && this->max.z == other.min.z) || (!touch && this->max.z <= other.min.z))
			&& this->min.y < other.max.y
			&& other.min.y < this->max.y
			&& this->min.x < other.max.x
			&& other.min.x < this->max.x);
	}

	bool Item::isAbove(Item& other, const bool touch) {
		return other.isBelow(*this, touch);
	}
	bool Item::isBehind(Item& other) {
		if (this->id == other.id) return false;

		return
			this->max.x <= other.min.x &&
			this->max.z > other.min.z &&
			this->min.z < other.max.z&&
			this->max.y > other.min.y &&
			this->min.y < other.max.y;
	}

	bool Item::isInFront(Item& other) {
		return other.isBehind(*this);
	}

}