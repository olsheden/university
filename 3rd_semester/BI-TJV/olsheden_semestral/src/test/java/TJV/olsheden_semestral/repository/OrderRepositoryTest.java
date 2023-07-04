package TJV.olsheden_semestral.repository;
import TJV.olsheden_semestral.domain.Client;
import TJV.olsheden_semestral.domain.Order;
import TJV.olsheden_semestral.domain.Restaurant;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;
import org.springframework.test.context.junit4.SpringRunner;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Set;

import static org.junit.Assert.assertEquals;

@RunWith(SpringRunner.class)
@DataJpaTest
public class OrderRepositoryTest {
    @Autowired
    private OrderReposiroty orderRepository;
    @Autowired
    private ClientRepository clientRepository;
    @Autowired
    private RestaurantRepository restaurantRepository;

    @Test
    public void testCountClientsWithAllProducts() {
        // Insert test data into the repositories
        Client client1 = new Client(1L, "client1", "surname1" , 31L);
        Client client2 = new Client(2L, "client2", "surname2" , 32L);
        Client client3 = new Client(3L, "client3", "surname3" , 33L);
        clientRepository.save(client1);
        clientRepository.save(client2);
        clientRepository.save(client3);

        Restaurant restaurant1 = new Restaurant(1L, "restaurant1", "address1");
        Restaurant restaurant2 = new Restaurant(2L, "restaurant2", "address2");
        restaurantRepository.save(restaurant1);
        restaurantRepository.save(restaurant2);

        Order order1 = new Order(1L, LocalDateTime.now(), 100L, List.of("productType1", "productType2", "productType3"), 10L, client1, Set.of(restaurant1, restaurant2));
        Order order2 = new Order(2L, LocalDateTime.now(), 200L, List.of("productType1", "productType2"), 20L, client2, Set.of(restaurant1));
        Order order3 = new Order(3L, LocalDateTime.now(), 300L, List.of("productType1", "productType3"), 30L, client3, Set.of(restaurant2));
        orderRepository.save(order1);
        orderRepository.save(order2);
        orderRepository.save(order3);

        // Call the method and assert the result
        Long result = orderRepository.countClientsWithAllProducts("productType1", "productType2", "productType3");
        assertEquals(Long.valueOf(1), result);
    }
}