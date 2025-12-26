// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTest_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_Test;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_Test()
	{
		if (!Z_Registration_Info_UPackage__Script_Test.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/Test",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0xA7300A13,
				0x7E0BDE9E,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_Test.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_Test.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_Test(Z_Construct_UPackage__Script_Test, TEXT("/Script/Test"), Z_Registration_Info_UPackage__Script_Test, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xA7300A13, 0x7E0BDE9E));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
