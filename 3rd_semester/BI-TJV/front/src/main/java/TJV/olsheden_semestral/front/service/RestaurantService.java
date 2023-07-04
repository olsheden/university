package TJV.olsheden_semestral.front.service;


import TJV.olsheden_semestral.front.client_api.RestaurantClient;
import TJV.olsheden_semestral.front.domain.RestaurantDto;
import org.springframework.stereotype.Service;

import java.util.Collection;
import java.util.Optional;

@Service
public class RestaurantService {
    private RestaurantClient restaurantClient;

    public RestaurantService(RestaurantClient restaurantClient) {
        this.restaurantClient = restaurantClient;
    }

    public void create(RestaurantDto e) {
        restaurantClient.create(e);
    }

    public Collection<RestaurantDto> readAll() {
        return restaurantClient.readAll();
    }

    public Optional<RestaurantDto> readOne() {
        return restaurantClient.readOne();
    }

    public void setCurrentRestaurant(long id) {
        restaurantClient.setCurrentRestaurant(id);
    }

    public void update(RestaurantDto e) {
        restaurantClient.updateOne(e);
    }

    public void update(String name, String address, Collection<Long> orderId) {
        var cur = restaurantClient.readOne();
        if (cur.isPresent()) {
            var restaurant = cur.get();
            restaurant.name = name;
            restaurant.address = address;
            restaurant.orderId = orderId;
            update(restaurant);
        }
    }

    public void deleteOne() {
        restaurantClient.deleteOne();
    }
}
