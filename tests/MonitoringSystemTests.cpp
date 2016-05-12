//
// Created by duncan on 5/7/16.
//

#include <ConstantSignal.hpp>
#include <AngularSensor.hpp>
#include <SineSignal.hpp>
#include <PressureSensor.hpp>
#include <SawtoothSignal.hpp>
#include <TemperatureSensor.hpp>
#include <VibrationSensor.hpp>
#include <fstream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MonitoringSystem.hpp"
#include "SawtoothSignalTests.hpp"
#include "SineSignalTests.hpp"

using namespace Camax;


class MonitoringSystemTests : public ::testing::Test
{
public:
    void SetUp() {}

    void TearDown() {}

private:
};

string verificationString(Time timeStamp, string sensorName, double sensorVoltage, string sensorUnits)
{
    stringbuf buffer;
    ostream os(&buffer);

    os << timeStamp << ", sensor: " << sensorName << ", measurement: " << sensorVoltage << " (" << sensorUnits << ")\n";

    return buffer.str();
}

TEST_F(MonitoringSystemTests, ConstructAndUseOneSensor)
{
    stringbuf buffer;
    ostream os(&buffer);
    MonitoringSystem monitor(os);

    double voltage = 23.45;
    Time timeOffset(0, 0, 0);
    Signal *signal = new ConstantSignal(voltage, timeOffset);
    Sensor *sensor = new AngularSensor("Direction", *signal);

    monitor.AddSensor(sensor);
    Time samplingTime(0, 23, 45);
    monitor.TakeReading(samplingTime);

    string checkString = verificationString(samplingTime, "Direction", voltage, "radians");
    EXPECT_EQ(checkString, buffer.str());
}

TEST_F(MonitoringSystemTests, ConstructAndUseOneSensorWriteToFile)
{
    string logFileName = "monitorLog.txt";
    filebuf buffer;
    buffer.open(logFileName , std::ios::out);
    ostream os(&buffer);
    MonitoringSystem monitor(os);

    double voltage = 23.45;
    Time timeOffset(0, 0, 0);
    Signal *signal = new ConstantSignal(voltage, timeOffset);
    Sensor *sensor = new AngularSensor("Direction", *signal);

    monitor.AddSensor(sensor);
    Time samplingTime(0, 23, 45);
    monitor.TakeReading(samplingTime);

    buffer.close();

    filebuf ibuffer;
    ibuffer.open(logFileName, std::ios::in);
    istream istream1 (&ibuffer);

    string line;
    string fileContents;

    while(getline(istream1, line))
    {
        fileContents += line;
        fileContents.push_back('\n');
    }

    string checkString = verificationString(samplingTime, "Direction", voltage, "radians");
    EXPECT_EQ(checkString, fileContents);
}

TEST_F(MonitoringSystemTests, ManySensors)
{
    stringbuf buffer;
    ostream os(&buffer);
    MonitoringSystem monitor(os);

    double voltage = 23.45;
    Time timeOffset(0, 0, 0);
    Signal *signal = new ConstantSignal(voltage, timeOffset);
    Sensor *sensor = new AngularSensor("Direction", *signal);

    monitor.AddSensor(sensor);
    Time samplingTime(0, 23, 45);
    monitor.TakeReading(samplingTime);
    string checkString = verificationString(samplingTime, "Direction", voltage, "radians");
    EXPECT_EQ(checkString, buffer.str());

    buffer.str("");

    signal = new SineSignal(voltage, timeOffset, 0, 10, Time(0, 1, 0));
    sensor = new PressureSensor("Pressure", *signal);
    monitor.AddSensor(sensor);
    monitor.TakeReading(samplingTime);
    checkString += verificationString(samplingTime, "Pressure", voltage, "Pounds per square inch (PSI)");
    EXPECT_EQ(checkString, buffer.str());

    buffer.str("");

    signal = new SawtoothSignal(voltage, timeOffset, 0, 10, Time(0, 1, 0));
    sensor = new TemperatureSensor("Temperature", *signal);
    monitor.AddSensor(sensor);
    monitor.TakeReading(samplingTime);
    checkString += verificationString(samplingTime, "Temperature",
                                      SawTests::saw(voltage, timeOffset, 0, 10, Time(0, 1, 0), samplingTime), "Degrees Celsius");
    EXPECT_EQ(checkString, buffer.str());

    buffer.str("");

    signal = new ConstantSignal(voltage, timeOffset);
    sensor = new VibrationSensor("Vibration", *signal);
    monitor.AddSensor(sensor);
    monitor.TakeReading(samplingTime);
    checkString += verificationString(samplingTime, "Vibration", voltage, "Hertz (Hz)");
    EXPECT_EQ(checkString, buffer.str());
}

TEST_F(MonitoringSystemTests, ConstructAndUseManySensorsWriteToFile)
{
    string logFileName = "monitorManyLog.txt";
    filebuf buffer;
    buffer.open(logFileName , std::ios::out);
    ostream os(&buffer);
    MonitoringSystem monitor(os);

    double voltage = 23.45;
    Time timeOffset(0, 0, 0);
    Signal *signal = new ConstantSignal(voltage, timeOffset);
    Sensor *sensor = new AngularSensor("Direction", *signal);
    Time samplingTime(0, 23, 45);

    monitor.AddSensor(sensor);
    string checkString = verificationString(samplingTime, "Direction", voltage, "radians");

    signal = new SineSignal(voltage, timeOffset, 0, 10, Time(0, 1, 0));
    sensor = new PressureSensor("Pressure", *signal);
    monitor.AddSensor(sensor);
    checkString += verificationString(samplingTime, "Pressure", voltage, "Pounds per square inch (PSI)");

    signal = new SawtoothSignal(voltage, timeOffset, 0, 10, Time(0, 1, 0));
    sensor = new TemperatureSensor("Temperature", *signal);
    monitor.AddSensor(sensor);
    checkString += verificationString(samplingTime, "Temperature",
                                      SawTests::saw(voltage, timeOffset, 0, 10, Time(0, 1, 0), samplingTime), "Degrees Celsius");

    signal = new ConstantSignal(voltage, timeOffset);
    sensor = new VibrationSensor("Vibration", *signal);
    monitor.AddSensor(sensor);
    checkString += verificationString(samplingTime, "Vibration", voltage, "Hertz (Hz)");

    monitor.TakeReading(samplingTime);

    buffer.close();

    filebuf ibuffer;
    ibuffer.open(logFileName, std::ios::in);
    istream istream1 (&ibuffer);

    string line;
    string fileContents;

    while(getline(istream1, line))
    {
        fileContents += line;
        fileContents.push_back('\n');
    }

    EXPECT_EQ(checkString, fileContents);
}

TEST_F(MonitoringSystemTests, ConstructAndUseManySensorsWriteToFileMultipleSamplingTimes)
{
    string logFileName = "monitorManyLog.txt";
    filebuf buffer;
    buffer.open(logFileName , std::ios::out);
    ostream os(&buffer);
    MonitoringSystem monitor(os);

    double voltage = 23.45;
    Time timeOffset(0, 0, 0);
    Signal *signal = new ConstantSignal(voltage, timeOffset);
    Sensor *sensor = new AngularSensor("Direction", *signal);

    monitor.AddSensor(sensor);
//    string checkString = verificationString(samplingTime, "Direction", voltage, "radians");

    signal = new SineSignal(voltage, timeOffset, 0, 10, Time(0, 1, 0));
    sensor = new PressureSensor("Pressure", *signal);
    monitor.AddSensor(sensor);
//    checkString += verificationString(samplingTime, "Pressure", voltage, "Pounds per square inch (PSI)");

    signal = new SawtoothSignal(voltage, timeOffset, 0, 10, Time(0, 1, 0));
    sensor = new TemperatureSensor("Temperature", *signal);
    monitor.AddSensor(sensor);
//    checkString += verificationString(samplingTime, "Temperature",
//                                      SawTests::saw(voltage, timeOffset, 0, 10, Time(0, 1, 0), samplingTime), "Degrees Celsius");

    signal = new ConstantSignal(voltage, timeOffset);
    sensor = new VibrationSensor("Vibration", *signal);
    monitor.AddSensor(sensor);
//    checkString += verificationString(samplingTime, "Vibration", voltage, "Hertz (Hz)");

    Time samplingTime(0, 0, 0);
    string checkString;
    int iterations = 1;
    for(int i = 0; i < iterations; i++)
    {
        samplingTime += Time(0, 1, 0);
        monitor.TakeReading(samplingTime);

        checkString += verificationString(samplingTime, "Direction", voltage, "radians");
//        checkString += verificationString(samplingTime, "Pressure", voltage, "Pounds per square inch (PSI)");
        checkString += verificationString(samplingTime, "Pressure",
                                          SineTest::sine(voltage, timeOffset, 0, 10, Time(0, 1, 0), samplingTime), "Pounds per square inch (PSI)");
        checkString += verificationString(samplingTime, "Temperature",
                                          SawTests::saw(voltage, timeOffset, 0, 10, Time(0, 1, 0), samplingTime), "Degrees Celsius");
        checkString += verificationString(samplingTime, "Vibration", voltage, "Hertz (Hz)");
    }

    buffer.close();

    filebuf ibuffer;
    ibuffer.open(logFileName, std::ios::in);
    istream istream1 (&ibuffer);

    string line;
    string fileContents;

    while(getline(istream1, line))
    {
        fileContents += line;
        fileContents.push_back('\n');
    }

    EXPECT_EQ(checkString, fileContents);
}
