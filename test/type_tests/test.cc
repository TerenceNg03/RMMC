#include <gtest/gtest.h>
#include "rmm_types.hh"
#include <vector>
#include <functional>

using namespace rmmc;

TEST(Basic, built_in_types){
	std::vector<std::function<rmm_type()>> make_types = {
		make_u8,
		make_u16,
		make_u32,
		make_u64,
		make_i8,
		make_i16,
		make_i32,
		make_i64,
		make_f32,
		make_f64,
		make_bool
	};

	std::vector<rmm_type> types;

	for(auto f: make_types){
		rmm_type t = f();
		// test different
		EXPECT_EQ(std::find(types.begin(), types.end(), t), types.end());
		types.push_back(t);
	}
}

TEST(Advanced, array) {
	rmm_type t = make_array(make_u8(), 9);
	rmm_type t1 = make_array(make_u8(), 3);
	rmm_type t2 = make_array(make_bool(), 9);
	rmm_type t3 = make_array(make_i32());
	rmm_type t4 = make_array(make_i32());
	rmm_type t5 = make_array(make_u8(), 9);
	rmm_type t6 = make_array(make_i8());

	std::cout<<"t: "<<t.str()<<std::endl;
	std::cout<<"t2: "<<t2.str()<<std::endl;
	EXPECT_EQ(t, t5);
	EXPECT_EQ(t3, t4);

	EXPECT_TRUE(t != t1);
	EXPECT_TRUE(t != t2);
	EXPECT_TRUE(t3 != t6);
}
TEST(Advanced, pointer) {
	rmm_type t = make_pointer(make_array(make_i8(), 9));
	rmm_type t1 = make_pointer(make_array(make_i32(), 9));

	EXPECT_TRUE(t != t1);
}






TEST(Basic, traits){
	/* unique and ref not compatible */
	EXPECT_EQ(make_traits(true, true, true), std::nullopt);
	EXPECT_EQ(make_traits(false, true, true), std::nullopt);

	EXPECT_TRUE(make_traits(false, false, true)!=std::nullopt);
	EXPECT_TRUE(make_traits(false, true, false)!=std::nullopt);
	EXPECT_TRUE(make_traits(true, false, true)!=std::nullopt);
}



int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
