package TJV.olsheden_semestral.converter;

import TJV.olsheden_semestral.domain.Order;
import TJV.olsheden_semestral.domain.Restaurant;
import TJV.olsheden_semestral.dtos.RestaurantDto;
import TJV.olsheden_semestral.service.OrderService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.function.Function;

@Component
public class RestaurantConverterToEntity implements Function<RestaurantDto, Restaurant> {

    @Autowired
    private final OrderService orderService;

    public RestaurantConverterToEntity(OrderService orderService) {
        this.orderService = orderService;
    }

    @Override
    public Restaurant apply(RestaurantDto restaurantDto) {
        Collection<Order> orders = new ArrayList<>();
        for (Long orderId : restaurantDto.getOrderId()) {
            orders.add(orderService.readById(orderId).orElseThrow());
        }
        return new Restaurant( restaurantDto.id, restaurantDto.name, restaurantDto.address, new HashSet<>(orders));
    }
}
