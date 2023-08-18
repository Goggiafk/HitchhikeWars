#include "InventoryItemWidget.h"

#include "MyGamePlayerController.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"
#include "Kismet/GameplayStatics.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"

void UInventoryItemWidget::SetInventoryItem(UInventoryItem* Item)
{
	if (Item)
	{
		NameText = Cast<UTextBlock>(GetWidgetFromName("NameText"));
		QuantityText = Cast<UTextBlock>(GetWidgetFromName("QuantityText"));
		IconImage = Cast<UImage>(GetWidgetFromName("IconImage"));
		ItemButton = Cast<UButton>(GetWidgetFromName("ItemButton"));
		
		InventoryItem = Item;
		if (IconImage && Item->Icon)
		{
			IconImage->SetBrushFromTexture(Item->Icon);
		}
		if (NameText)
		{
			NameText->SetText(FText::FromString(Item->Name));
		}
		if (QuantityText)
		{
			QuantityText->SetText(FText::AsNumber(Item->Quantity));
		}

		ItemButton->OnClicked.AddDynamic(this, &UInventoryItemWidget::OnButtonClicked);
	}
}

void UInventoryItemWidget::OnButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Item type is: %u"), InventoryItem->Type);
	switch (InventoryItem->Type)
	{
		// case EItemType::Bullets:
		// Cast<ATP_ThirdPersonCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->SetRifle();
		// break;
		case EItemType::Rifle:
			Cast<ATP_ThirdPersonCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->SetRifle();
			break;
	}
}
