#include<proxyInclude/gtest>
#include "MDD/OptTraced.h"

std::string msg="Error 404: Humor Not Found";
auto val=42;
std::string val2="Les tests, ce n'est pas de la documentation ; la documentation, c'est la documentation <3";

OptTraced<int> fail(){
	return std::nullopt;
}
OptTraced<int> failMsg(){
	return OptT::err(msg);
}
OptTraced<int> failTrace(){
	return OptT::trace();
}
OptTraced<int> failTraceMsg(){
	return OptT::tracedErr(msg);
}
OptTraced<int> succeed(){
	return val;
}
OptTraced<std::string> succeed2(){
	return val2;
}


TEST(AuroraMDD, OptTraced_fail){
	auto result = fail();
	EXPECT_FALSE(result);
}
TEST(AuroraMDD, OptTraced_failMsg){
	auto result = failMsg();
	EXPECT_FALSE(result);
	EXPECT_EQ(result.msgs.front(),msg);
	EXPECT_EQ(result.msgs.size(),1);
}
TEST(AuroraMDD, OptTraced_failTrace){
	auto result = failTrace();
	EXPECT_FALSE(result);
	EXPECT_EQ(result.msgs.size(),32);//tested to be that value
	result.print();
}
TEST(AuroraMDD, OptTraced_failTraceMsg){
	auto result = failTraceMsg();
	EXPECT_FALSE(result);
	EXPECT_EQ(result.msgs.size(),35);//tested to be that value
	EXPECT_EQ(result.msgs.back(),msg);
	result.print();
}

TEST(AuroraMDD, OptTraced_succeed){
	auto result = succeed();
	EXPECT_TRUE(result);
	EXPECT_EQ(result.value(),val);
}
TEST(AuroraMDD, OptTraced_succeed2){
	auto result = succeed2();
	EXPECT_TRUE(result);
	EXPECT_EQ(result.value(),val2);
}
