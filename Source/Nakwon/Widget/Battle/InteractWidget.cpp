// Fill out your copyright notice in the Description page of Project Settings.


#include "../Battle/InteractWidget.h"

#include "Components/Image.h"

void UInteractWidget::InitWidget()
{
	Img_CrossHair->SetVisibility(ESlateVisibility::Collapsed);
}