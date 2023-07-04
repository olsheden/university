package TJV.olsheden_semestral.controller;

import TJV.olsheden_semestral.Exception.FieldsCannotBeEmpty;
import TJV.olsheden_semestral.Exception.InvalidStateException;
import TJV.olsheden_semestral.Exception.NotFoundException;
import TJV.olsheden_semestral.converter.OrderConverterToDto;
import TJV.olsheden_semestral.converter.OrderConvertertoEntity;
import TJV.olsheden_semestral.domain.Order;
import TJV.olsheden_semestral.dtos.OrderDto;
import TJV.olsheden_semestral.service.ClientService;
import TJV.olsheden_semestral.service.RestaurantService;
import TJV.olsheden_semestral.service.OrderService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.bind.annotation.RequestMapping;

import java.util.Collection;
import java.util.function.Function;
import java.util.stream.StreamSupport;

@RestController
@RequestMapping("/orders")
public class OrderController {
    @Autowired
    protected OrderService orderService;

    @Autowired
    protected Function<Order, OrderDto> orderConverterToDto;

    @Autowired
    protected Function<OrderDto, Order> orderConvertertoEntity;

    public OrderController(OrderService orderService, Function<Order, OrderDto> orderConverterToDto, Function<OrderDto, Order> orderConvertertoEntity) {
        this.orderService = orderService;
        this.orderConverterToDto = orderConverterToDto;
        this.orderConvertertoEntity = orderConvertertoEntity;
    }

    @PostMapping
    public OrderDto createOrder(@RequestBody OrderDto orderDto) throws FieldsCannotBeEmpty, InvalidStateException {
        return orderConverterToDto.apply(orderService.create(orderConvertertoEntity.apply(orderDto)));
    }

    @GetMapping("/{id}")
    public ResponseEntity<OrderDto> readOne(@PathVariable Long id) throws NotFoundException {
        var res = orderService.readById(id);
        if (res.isPresent())
            return ResponseEntity.ok(orderConverterToDto.apply(res.get()));
        else
            return ResponseEntity.notFound().build();

    }

    @GetMapping
    public Collection<OrderDto> readAll(){
        return StreamSupport.stream(orderService.readAll().spliterator(),false).map(orderConverterToDto).toList();
    }

    @PutMapping("/{id}")
    public void update(@RequestBody OrderDto orderDto, @PathVariable Long id) throws FieldsCannotBeEmpty, NotFoundException {
        Order order = orderService.readById(id).orElseThrow();
        orderDto.date = order.getDate();
        orderService.update(orderConvertertoEntity.apply(orderDto));
    }

    @DeleteMapping("/{id}")
    public void deleteOrder(@PathVariable Long id) throws NotFoundException {
        orderService.deleteById(id);
    }

    @GetMapping("/count")
    public Long countCustomersWithAllProductTypes() {
        return orderService.countCustomersWithAllProductTypes();
    }

}

