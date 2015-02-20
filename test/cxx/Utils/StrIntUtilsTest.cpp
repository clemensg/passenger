#include "TestSupport.h"
#include <Utils/StrIntUtils.h>

using namespace Passenger;
using namespace std;

namespace tut {
	struct StrIntUtilsTest {
	};

	void testTruncate(const char* str, const char *tokens, int maxBetweenTokens, const char* expected) {
		std::stringstream sstream;
		truncateBeforeTokens(str, tokens, maxBetweenTokens, sstream);
		ensure("got [" +  sstream.str() + "], expected [" + expected + "]", sstream.str() == expected);
	}
	
	DEFINE_TEST_GROUP(StrIntUtilsTest);

	TEST_METHOD(1) { // expecting no change
		testTruncate("", "", 0, "");
		testTruncate("testwithout/tokens", "", 2, "testwithout/tokens");
		testTruncate("", "/", 2, "");
		testTruncate("/", "", 2, "/");
		testTruncate("/", "/", 2, "/");
		testTruncate("hello", "/", 2, "hello");
		testTruncate("/hello", "/", 3, "/hello");
	} TEST_METHOD(2) { // begin/end token maintain while truncate
		testTruncate("hello/", "/", 3, "hel/");
		testTruncate("/hello/", "/", 3, "/hel/");
	} TEST_METHOD(3) { // exact truncate and multiple split tokens
		testTruncate("hello/world/Main.cpp", "/", 2, "he/wo/Main.cpp");
		testTruncate("hello/world\\Main.cpp", "/\\", 1, "h/w\\Main.cpp");
		testTruncate("hello/world\\Main.cpp", "/", 1, "h/world\\Main.cpp");
		testTruncate("/he/llo/worl/", "/", 3, "/he/llo/wor/");
	}
}
