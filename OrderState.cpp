#include "OrderState.h"
#include "PizzaOrders.h"

void OrderState::changeState(PizzaOrders* context, OrderState* newState) {
    context->setState(newState);
}