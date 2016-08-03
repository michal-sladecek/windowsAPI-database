#include "stdafx.h"
#include "gtest\gtest.h"

#include "Patient.h"
#include "Databaza.h"

class PatientTest : public ::testing::Test
{
protected:
	Patient p;
	std::wstring m_name = L"Michal SLádeèek";
	std::wstring m_birthNumber = L"220698/1234";
	std::wstring m_phoneNumber = L"0944949652";
	std::wstring m_insurance = L"VSZP";
	std::wstring m_doctor = L"MuDr. Analfabet Kokotsky";
	std::wstring m_note = L"This is note|[]123432]]]][123";
	virtual void SetUp()
	{
		p = Patient(m_name, m_birthNumber, m_phoneNumber,
			m_insurance, m_doctor, m_note);
	}
};

TEST_F(PatientTest, SettersGetters)
{
	EXPECT_EQ(p.getBirthNumber(), m_birthNumber);
	EXPECT_EQ(p.getNote(), m_note);
	p.setBirthNumber(L"12345");
	EXPECT_EQ(p.getBirthNumber(), L"12345");
	p.setBirthNumber(m_birthNumber);
	EXPECT_EQ(p.getBirthNumber(), m_birthNumber);
}

TEST_F(PatientTest, Export)
{
	std::string exported = p.ExportSerialize();
	Patient s;
	s.Load(exported);
	EXPECT_EQ(p.getBirthNumber(), s.getBirthNumber());
	EXPECT_EQ(p.getName(), s.getName());
	EXPECT_EQ(p.getID(), s.getID());
	EXPECT_EQ(p.getIDasString(), s.getIDasString());
	EXPECT_EQ(p.getNote(), s.getNote());
	EXPECT_EQ(p.getInsurance(), s.getInsurance());
	EXPECT_EQ(p.getDoctor(), s.getDoctor());
	EXPECT_EQ(p.getPhoneNumber(), s.getPhoneNumber());
}

class DatabaseTest : public ::testing::Test 
{
protected:
	Database db;
	virtual void SetUp()
	{
		db.LoadFromFile(L"C:\\Users\\USER\\Documents\\Visual Studio 2015\\Projects\\babiakAmbulancia\\databaza100");
	}
};

TEST_F(DatabaseTest, isDBLoaded)
{
	EXPECT_GE(db.NumberOfPatients(), 100);
}

TEST_F(DatabaseTest, Export)
{
	db.SaveToFile(L"tempDatabaseTested");
	Database db2;
	db2.LoadFromFile(L"tempDatabaseTested");
	EXPECT_EQ(db.NumberOfPatients(), db2.NumberOfPatients());
}
