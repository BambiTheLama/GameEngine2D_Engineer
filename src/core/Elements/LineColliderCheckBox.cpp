#include "LineColliderCheckBox.h"
#include "VectorEnter.h"

LineColliderCheckBox::LineColliderCheckBox(Rectangle pos, std::string text, bool* isPress, ItemProperty* prop) :CheckBoxOpenElements(pos, text, isPress)
{
	this->prop = prop;
	this->last = 0;
}

void LineColliderCheckBox::updateVectorPoints()
{
	int n = last;
	last = prop->nPoints;
	if (n < last)
	{
		for (int i = n; i < last; i++)
		{
			Rectangle pos=componetPos;
			pos.y += pos.height;
			pos.height = 32;
			VectorEnter* vec = new VectorEnter(pos, "Vec" + i, NULL);
			addElement(vec);
		}

	}
	else if (n > last)
	{
		for (int i = last; i < n; i++)
		{
			removeLastElement();
		}
	}
	n = 0;
	prop->updatePointsToCollisions();
	for (Element* e : elements)
	{
		VectorEnter* vec = dynamic_cast<VectorEnter*>(e);
		if (vec == NULL)
			continue;
		vec->updateVal(&prop->points[n]);
		n++;
		if (n >= last)
			return;
	}
}

void LineColliderCheckBox::update()
{
	CheckBoxOpenElements::update();
}

bool LineColliderCheckBox::press()
{
	updateVectorPoints();
	bool p = CheckBoxOpenElements::press();
	if (p)
	{
		return true;
	}
	return false;
}

void LineColliderCheckBox::draw()
{
	updateVectorPoints();
	CheckBoxOpenElements::draw();
}

void LineColliderCheckBox::reloadData()
{
	updateVectorPoints();
}