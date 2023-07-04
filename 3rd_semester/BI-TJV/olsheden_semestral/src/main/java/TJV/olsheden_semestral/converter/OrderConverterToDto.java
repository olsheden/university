package TJV.olsheden_semestral.converter;

import TJV.olsheden_semestral.Exception.NotFoundException;
import TJV.olsheden_semestral.domain.Client;
import TJV.olsheden_semestral.domain.Order;
import TJV.olsheden_semestral.domain.Restaurant;
import TJV.olsheden_semestral.dtos.OrderDto;
import TJV.olsheden_semestral.dtos.RestaurantDto;
import TJV.olsheden_semestral.service.RestaurantService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Set;
import java.util.function.Function;

@Component
public class OrderConverterToDto implements Function<Order, OrderDto> {

    @Autowired
    private RestaurantService restaurantService;

    public OrderConverterToDto(RestaurantService restaurantService) {
        this.restaurantService = restaurantService;
    }

    @Override
    public OrderDto apply(Order order) {
        OrderDto orderDto = new OrderDto();
        orderDto.setId(order.getId());
        orderDto.setDate(order.getDate());
        orderDto.setSumma(order.getSumma());
        orderDto.setTips(order.getTips());
        orderDto.setProduct_type(order.getProduct_type());
        orderDto.setClientId(order.getClient().getId());
        Collection<Long> restaurantsIds = new ArrayList<>();
        for (Restaurant restaurant : order.getRestaurants()) {
            restaurantsIds.add(restaurant.getId());
        }
        orderDto.setRestaurantsId(restaurantsIds);
        return orderDto;
    }
}
