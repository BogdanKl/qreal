#include "property.h"

#include <QDebug>

Property::Property(qrRepo::RepoApi *api, qReal::Id const &id) : mApi(api), mId(id)
{

}

bool Property::init()
{
	mIsEnum = false;
	mIsReference = false;
	mName = mApi->name(mId);
	if (mName.isEmpty()) {
		qDebug() << "ERROR: anonymous property found";
		return false;
	}
	mType = mApi->stringProperty(mId, "attributeType");
	if (mType.isEmpty()) {
		qDebug() << "ERROR: empty type of property found";
		return false;
	}

	mDefaultValue = mApi->stringProperty(mId, "defaultValue");
	return true;
}


QString Property::name()
{
	return mName;
}

QString Property::type()
{
	return mType;
}

QString Property::defaultValue()
{
	return mDefaultValue;
}

Property * Property::clone()
{
	Property *result = new Property(mApi, mId);
	result->mName = mName;
	result->mType = mType;
	result->mIsEnum = mIsEnum;
	result->mIsReference = mIsReference;
	result->mDescription = mDescription;
	result->mDefaultValue = mDefaultValue;
	return result;
}

bool Property::operator == (Property const &other) const
{
	return other.mName == mName
		&& other.mType == mType
		&& other.mIsEnum == mIsEnum
		&& other.mIsReference == mIsReference
		&& other.mDescription == mDescription
		&& other.mDefaultValue == mDefaultValue
		;
}

bool Property::operator != (Property const &other) const
{
	return !(other == *this);
}

void Property::print() const
{
	qDebug() << "property"
			<< "\t" << mName
			<< "\t" << mType
			<< "\t" << mIsEnum
			<< "\t" << mIsReference
			<< "\t" << mDescription
			<< "\t" << mDefaultValue;
}