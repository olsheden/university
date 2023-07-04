package TJV.olsheden_semestral.converter;

import TJV.olsheden_semestral.domain.Order;
import TJV.olsheden_semestral.domain.Restaurant;
import TJV.olsheden_semestral.dtos.RestaurantDto;
import TJV.olsheden_semestral.service.OrderService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.Collection;
import java.util.function.Function;

@Component
public class RestaurantConvertertoDto implements Function<Restaurant, RestaurantDto> {

    @Autowired
    protected final OrderService orderService;

    public RestaurantConvertertoDto(OrderService orderService) {
        this.orderService = orderService;
    }

    @Override
    public RestaurantDto apply(Restaurant restaurant) {
        RestaurantDto restaurantDto = new RestaurantDto();
        restaurantDto.setId(restaurant.getId());
        restaurantDto.setName(restaurant.getName());
        restaurantDto.setAddress(restaurant.getAddress());
        Collection<Long> ordersIds = new ArrayList<>();
        for (Order order : restaurant.getOrderItems()) {
            ordersIds.add(order.getId());
        }
        restaurantDto.setOrderId(ordersIds);
        return restaurantDto;
    }
}
