package TJV.olsheden_semestral.front.service;


import TJV.olsheden_semestral.front.client_api.OrderClient;
import TJV.olsheden_semestral.front.domain.OrderDto;
import org.springframework.stereotype.Service;

import java.util.Collection;
import java.util.List;
import java.util.Optional;

@Service
public class OrderService {
    private OrderClient orderClient;

    public OrderService(OrderClient orderClient) {
        this.orderClient = orderClient;
    }

    public void create(OrderDto e) {
        orderClient.create(e);
    }

    public Collection<OrderDto> readAll() {
        return orderClient.readAll();
    }

    public Optional<OrderDto> readOne() {
        return orderClient.readOne();
    }

    public void setCurrentOrder(long id) {
        orderClient.setCurrentOrder(id);
    }

    public void update(OrderDto e) {
        orderClient.updateOne(e);
    }

    public void update(Long summa, List<String> product, Long tips, Long clientId, Collection<Long> restaurantsId) {
        var cur = orderClient.readOne();
        if (cur.isPresent()) {
            var order = cur.get();
            order.summa = summa;
            order.product_type = product;
            order.tips = tips;
            order.clientId = clientId;
            order.restaurantsId = restaurantsId;
            update(order);
        }
    }

    public void deleteOne() {
        orderClient.deleteOne();
    }

    public Long countCustomersWithAllProductTypes() {
        return orderClient.countClientsWithAllProducts("apple", "juice", "bread");
    }
}
