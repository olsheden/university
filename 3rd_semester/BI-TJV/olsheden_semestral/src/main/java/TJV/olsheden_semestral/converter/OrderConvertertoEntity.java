package TJV.olsheden_semestral.converter;

import TJV.olsheden_semestral.domain.Order;
import TJV.olsheden_semestral.domain.Restaurant;
import TJV.olsheden_semestral.dtos.OrderDto;
import TJV.olsheden_semestral.service.ClientService;
import TJV.olsheden_semestral.service.RestaurantService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Set;
import java.util.function.Function;

@Component
public class OrderConvertertoEntity implements Function<OrderDto, Order> {

    @Autowired
    protected final ClientService clientService;

    @Autowired
    protected final RestaurantService restaurantService;

    public OrderConvertertoEntity(ClientService clientService, RestaurantService restaurantService) {
        this.clientService = clientService;
        this.restaurantService = restaurantService;
    }

    @Override
    public Order apply(OrderDto orderDto) {
        Collection<Restaurant> restaurants = new ArrayList<>();
        for (Long restaurantId : orderDto.getRestaurantsId()) {
            restaurants.add(restaurantService.readById(restaurantId).orElseThrow());
        }
        return new Order(orderDto.id, orderDto.date, orderDto.summa, orderDto.product_type, orderDto.tips, clientService.readById(orderDto.clientId).orElseThrow(), new HashSet<>(restaurants) );
    }
}
