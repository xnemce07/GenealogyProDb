/*!
 *  \file   tst_testkernel.cpp
 *  \author Eva Navratilova
 */

#include "tst_testkernel.h"

QTEST_MAIN(TestKernel);

TestKernel::TestKernel()
{

}

TestKernel::~TestKernel()
{

}

void TestKernel::testImport()
{
    QString file1 = "../test/testdata/SampleAllData.ged";
    bool saveable, successful;
    Identifier first, last;
    int cycleCount = 0;

    successful = _kernel.importFile(file1, saveable);

    // Import ok
    QCOMPARE(successful, true);     // Should be imported successfuly
    QCOMPARE(saveable, true);       // Should be saveable - data was meant for this program

    // INDIVIDUAL count ok
    first = _kernel.record()->getIdentifierIndividualFirst();
    last = _kernel.record()->getIdentifierIndividualLast();
    QCOMPARE(first.getNumber(), static_cast<unsigned long long>(22));    // First identifier number
    QCOMPARE(last.getNumber(), static_cast<unsigned long long>(78 + 1)); // Last identifier number + 1
    for(Identifier it=first; it != last; _kernel.record()->getIdentifierIndividualNext(it))
    {
        cycleCount++;
    }
    QCOMPARE(cycleCount, 14);    // Total of 6 people in file1

    // FAMILY count ok
    cycleCount = 0;
    first = _kernel.record()->getIdentifierFamilyFirst();
    last = _kernel.record()->getIdentifierFamilyLast();
    QCOMPARE(static_cast<signed>(first.getNumber()), 16);        // First identifier number
    QCOMPARE(static_cast<signed>(last.getNumber()), 17 + 1);     // Lat identifier number + 1
    for(Identifier it=first; it != last; _kernel.record()->getIdentifierFamilyNext(it))
    {
        cycleCount++;
    }
    QCOMPARE(cycleCount, 2);    // Two families

    // SUBMITTER count ok
    cycleCount = 0;
    first = _kernel.record()->getIdentifierSubmitterFirst();
    last = _kernel.record()->getIdentifierSubmitterLast();
    QCOMPARE(static_cast<signed>(first.getNumber()), 0);        // First identifier number
    QCOMPARE(static_cast<signed>(last.getNumber()), 0 + 1);     // Lat identifier number + 1
    for(Identifier it=first; it != last; _kernel.record()->getIdentifierSubmitterNext(it))
    {
        cycleCount++;
    }
    QCOMPARE(cycleCount, 1);    // Exactly one submitter

    // SOURCE RECORD count ok
    cycleCount = 0;
    first = _kernel.record()->getIdentifierSourceFirst();
    last = _kernel.record()->getIdentifierSourceLast();
    QCOMPARE(static_cast<signed>(first.getNumber()), 0);        // First identifier number
    QCOMPARE(static_cast<signed>(last.getNumber()), 2 + 1);     // Lat identifier number + 1
    for(Identifier it=first; it != last; _kernel.record()->getIdentifierSourceNext(it))
    {
        cycleCount++;
    }
    QCOMPARE(cycleCount, 3);    // Three sources
}

void TestKernel::testSourceRecordDataImported()
{
    auto birtSrc = _kernel.record()->getSourceRefs(CommonEventType::BIRT);
    auto deatSrc = _kernel.record()->getSourceRefs(CommonEventType::DEAT);
    auto marrSrc = _kernel.record()->getSourceRefs(CommonEventType::MARR);

    // Should find single appearance of each
    QCOMPARE(birtSrc.length(), 1);
    QCOMPARE(deatSrc.length(), 1);
    QCOMPARE(marrSrc.length(), 1);

    birtSrc = _kernel.record()->getSourceRefs(CommonEventType::BIRT, Date(1844, 5, 2));
    // Should find Florian's Birth Source
    QCOMPARE(birtSrc.length(), 1);

    birtSrc = _kernel.record()->getSourceRefs(CommonEventType::BIRT, Date(1844, 5, 2), "Čelčice");
    // Should find Florian's Birth Source
    QCOMPARE(birtSrc.length(), 1);

}

void TestKernel::testIndividualDataImported()
{
    // Florian identifier init
    Identifier wife = _kernel.record()->getIdentifierIndividualFirst();
    auto husbands = _kernel.record()->getIndividualPartners(wife);

    QCOMPARE(husbands.length(), 1); // Should have exactly one husband
    if(! husbands.isEmpty())
    {
        _florian = _kernel.record()->getIndividualFather(husbands.first());
    }

    Identifier birtSrc = _kernel.record()->getIndividualBirthSourceRef(_florian);

    QCOMPARE(_kernel.record()->isSource(birtSrc), true);
    QCOMPARE(_kernel.record()->isSource(birtSrc), true);

    Identifier priest = _kernel.record()->getIndividualChristeningPriest(_florian);
    QCOMPARE(_kernel.record()->isIndividual(priest), true);

}

void TestKernel::testIndividualOccupation()
{
    unsigned int count = _kernel.record()->getIndividualOccuCount(_florian);
    QCOMPARE(count, static_cast<unsigned>(2));
}

void TestKernel::testDate()
{
    Date date(1850, 1, 1);
    QCOMPARE(date.year(), 1850);
    QCOMPARE(date.datePrecision(), DatePrecision::FULL);
    date = Date(1851);
    QCOMPARE(date.year(), 1851);
    QCOMPARE(date.datePrecision(), DatePrecision::YEAR);
}

