# include<stdio.h>
int main()
{
	int choice,no_of_bags,quality,price;
	float total_cost;
	printf("Welcome to starlight Farmers Association.We offer:\n");
	printf("1.shangi 50kg bag @3500\n");
	printf("2.supershangi 50kg bag @4000\n");
	printf("3.steven 50kg bag @3700\n");
	printf("4.Njoro 1 50kg bag @4500\n");
	
	printf("Enter your choice (1-4)=");
	scanf("%d",&choice);
		printf("Enter no_of_bags=");
	scanf("%d,",&no_of_bags);

	switch(choice)
{
	case 1:
		price=3500;
		break;
		case 2:
			price=4000;
			break;
			case 3:
			price=3700;
			break;
			case 4:
				price=4500;
				break;
				default:
					printf("invalid choice enter choice from 1-4\n");
					return 0;			
}

total_cost=price*no_of_bags;
printf("total cost is ksh%.2f\n",total_cost);
return 0;
}
