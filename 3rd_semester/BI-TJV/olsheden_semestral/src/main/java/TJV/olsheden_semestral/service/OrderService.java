package TJV.olsheden_semestral.service;

import TJV.olsheden_semestral.Exception.FieldsCannotBeEmpty;
import TJV.olsheden_semestral.Exception.InvalidStateException;
import TJV.olsheden_semestral.Exception.NotFoundException;
import TJV.olsheden_semestral.domain.Order;
import TJV.olsheden_semestral.repository.OrderReposiroty;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Collection;
import java.util.Optional;

@Service
public class OrderService {

    @Autowired
    protected final OrderReposiroty orderRepository;

    public OrderService(OrderReposiroty orderRepository) {
        this.orderRepository = orderRepository;
    }


    public Order create(Order order) throws FieldsCannotBeEmpty, InvalidStateException {
        Long id = order.getId();
        order.setDate(java.time.LocalDateTime.now());
        if(id != null && orderRepository.existsById(id))
            throw new InvalidStateException("Invalid state of order");
        if(order.getSumma() == null || order.getProduct_type() == null)
            throw new FieldsCannotBeEmpty("You should fill all the order's fields");
        return orderRepository.save(order);
    }

    public Optional<Order> readById(Long id) {
        return orderRepository.findById(id);
    }

    public Collection<Order> readAll() {
        return orderRepository.findAll();
    }

    public Order update(Order order) throws NotFoundException, FieldsCannotBeEmpty {
        if (orderRepository.findById(order.getId()).isEmpty()){
            throw new NotFoundException("Order not found");
        }
            return orderRepository.save(order);
    }

    public void deleteById(Long id) throws NotFoundException {

        if (orderRepository.findById(id).isEmpty())
            throw new NotFoundException("Order not found");

        orderRepository.deleteById(id);

    }

    public Long countCustomersWithAllProductTypes() {
        return orderRepository.countClientsWithAllProducts("apple", "juice", "bread");
    }
}