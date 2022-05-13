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

TEST(Basic, traits){
	/* unique and ref not compatible */
	EXPECT_EQ(make_traits(true, true, true), std::nullopt);
	EXPECT_EQ(make_traits(false, true, true), std::nullopt);

	EXPECT_TRUE(make_traits(false, false, true)!=std::nullopt);
	EXPECT_TRUE(make_traits(false, true, false)!=std::nullopt);
	EXPECT_TRUE(make_traits(true, false, true)!=std::nullopt);
}

TEST(Advanced, array) {
	rmm_type t = make_array(make_u8(), 9);
	rmm_type t1 = make_array(make_u8(), 3);
	rmm_type t2 = make_array(make_bool(), 9);
	rmm_type t3 = make_array(make_i32());
	rmm_type t4 = make_array(make_i32());
	rmm_type t5 = make_array(make_u8(), 9);
	rmm_type t6 = make_array(make_i8());

	EXPECT_EQ(t, t5);
	EXPECT_EQ(t3, t4);

	EXPECT_NE(t, t1);
	EXPECT_NE(t, t2);
	EXPECT_NE(t3, t6);
}

TEST(Advanced, pointer) {
	rmm_type t = make_pointer(make_array(make_i8(), 9));
	rmm_type t1 = make_pointer(make_array(make_i32(), 9));

	EXPECT_TRUE(t != t1);
}

TEST(Advanced, function){
	auto tr1 = *make_traits(false, false, false);
	auto tr2 = *make_traits(false, true, false);
	std::vector<std::pair<var_traits, rmm_type>> para1 = {
		{tr1, make_bool()}, 
		{tr2, make_array(make_f64(), 8)},
		{tr1, make_pointer(make_u8())}
	};
	std::vector<std::pair<var_traits, rmm_type>> para2 = {
		{tr1, make_bool()}, 
		{tr2, make_array(make_f64(), 8)},
		{tr2, make_pointer(make_u8())}
	};

	rmm_type func1 = make_function(para1.begin(), para1.end(), tr1, {});
	rmm_type func2 = make_function(para1.begin(), para1.end(), tr1, {});
	rmm_type func3 = make_function(para1.begin(), para1.end(), tr1, make_pointer(make_u8()));
	rmm_type func4 = make_function(para2.begin(), para2.end(), tr1, {});
	rmm_type func5 = make_function(para2.begin(), para2.end(), tr1, make_u8()); 
	rmm_type func6 = make_function(para2.begin(), para2.end(), tr2, make_u8());

	EXPECT_EQ(func1, func2);
	EXPECT_NE(func1, func3);
	EXPECT_NE(func1, func4);
	EXPECT_NE(func5, func6);

}

TEST(Advanced, compound) {
	auto tr = *make_traits(false, false, false);
	std::vector<std::pair<var_traits, rmm_type>> func_para = {
		{tr, make_bool()}, 
		{tr, make_array(make_f64(), 8)},
		{tr, make_pointer(make_u8())}
	};
	
	std::vector<std::tuple<var_traits, std::string, rmm_type>> cmp_types = {
		{tr, "a", make_array(make_i32(), 8)},
		{tr, "b", make_pointer(make_f64())},
		{tr, "func", make_function(
				func_para.begin(),
				func_para.end(),
				tr,
				make_f64()
				)
		}
	};

	std::vector<std::tuple<var_traits, std::string, rmm_type>> cmp_types2 = {
		{tr, "a3", make_array(make_u32(), 8)},
		{tr, "f4", make_pointer(make_f64())}
	};

	rmm_type comp1 = make_comp("comp1", cmp_types.begin(), cmp_types.end());
	rmm_type comp2 = make_comp("comp1", cmp_types2.begin(), cmp_types2.end());
	rmm_type comp3 = make_comp("comp2", cmp_types2.begin(), cmp_types2.end());

	EXPECT_EQ(comp1, comp2);
	EXPECT_NE(comp2, comp3);
}

TEST(Advanced, union_){
	auto tr = *make_traits(false, false, true);
	auto tr2 = *make_traits(false, false, false);
	std::vector<std::pair<var_traits, rmm_type>> func_para = {
		{tr, make_bool()}, 
		{tr2, make_array(make_f64(), 8)},
		{tr2, make_pointer(make_u8())}
	};
	
	std::vector<std::tuple<var_traits, std::string, rmm_type>> cmp_types = {
		{tr, "a", make_array(make_i32(), 8)},
		{tr, "b", make_pointer(make_f64())},
		{tr, "func", make_function(
				func_para.begin(),
				func_para.end(),
				tr,
				make_f64()
				)
		}
	};

	std::vector<std::tuple<var_traits, std::string, rmm_type>> cmp_types2 = {
		{tr, "a3", make_array(make_u32(), 8)},
		{tr2, "f4", make_pointer(make_f64())}
	};

	rmm_type union1 = make_union("union1", cmp_types.begin(), cmp_types.end());
	rmm_type union2 = make_union("union1", cmp_types2.begin(), cmp_types2.end());
	rmm_type union3 = make_union("union2", cmp_types2.begin(), cmp_types2.end());

	EXPECT_EQ(union1, union2);
	EXPECT_NE(union2, union3);
}



int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
