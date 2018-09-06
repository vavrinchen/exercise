//anyData() 讓實作 InterafaceDecoratorRTSP 的人可以在裡面換成想送的資料
//這裡假設 XMLData 這個 class 想傳送 XML 的資料, 
//當有其他 class 除了 video, audio, metadata 外還想送不同資料時, 只要改寫 anyData()

#include <string>  
#include <iostream>

class InterafaceRTSP
{
public:
	virtual void anyData() {};
	virtual void audioData() = 0;
	virtual void videoData() = 0;
	virtual void metaData() = 0;

};

class InterafaceDecoratorRTSP :public InterafaceRTSP
{
public:
	virtual void anyData() = 0;

};



class CustomizeRTSP :public InterafaceRTSP
{
public:
	CustomizeRTSP() { std::cout << "CustomizeRTSP initial" << std::endl; };
	~CustomizeRTSP() { std::cout << "CustomizeRTSP deconstruct" << std::endl; };
	void audioData() { std::cout << "CustomizeRTSP audioData" << std::endl; };
	void videoData() { std::cout << "CustomizeRTSP videoData" << std::endl; };
	void metaData() { std::cout << "CustomizeRTSP metaData" << std::endl; };

};


class XMLData :public InterafaceDecoratorRTSP
{
public:
	XMLData(InterafaceRTSP *rtsp) { this->rtsp = rtsp;  };
	void anyData() { std::cout << "this is XMLData" << std::endl; };
	void audioData() { rtsp->audioData(); };
	void videoData() { rtsp->videoData(); };
	void metaData() { rtsp->metaData(); };
private:
	InterafaceRTSP * rtsp;
};



int main(int argc, char* argv[])
{

	InterafaceRTSP *rtsp = new CustomizeRTSP();
	std::cout << "videoData: "  << std::endl;  
	rtsp->videoData();
	std::cout << "Now extend anyData in XMLData: " << std::endl;
	rtsp = new XMLData(rtsp);
	rtsp->anyData();
	system("pause");
	return 0;
}
