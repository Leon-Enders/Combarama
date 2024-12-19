#pragma once

enum class ECollisionResponseType
{
	ECR_Ignore,
	ECR_Overlap,
	ECR_Block
};

enum class ECollisionChannel
{
	ECC_None,
	ECC_WorldStatic,
	ECC_WorldDynamic,
	ECC_Projectile
};