package TJV.olsheden_semestral.converter;

import TJV.olsheden_semestral.domain.Client;
import TJV.olsheden_semestral.domain.Order;
import TJV.olsheden_semestral.dtos.ClientDto;
import TJV.olsheden_semestral.service.OrderService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.function.Function;

@Component
public class ClientConverterToEntity implements Function<ClientDto, Client> {

    @Autowired
    private final OrderService orderService;

    public ClientConverterToEntity(OrderService orderService) {
        this.orderService = orderService;
    }


    @Override
    public Client apply(ClientDto clientDto) {
        Collection<Order> orders = new ArrayList<>();
        for (Long orderId : clientDto.ordersId) {
            orders.add(orderService.readById(orderId).orElseThrow());
        }
        return new Client(clientDto.id, clientDto.name, clientDto.surname, clientDto.age,new HashSet<Order>(orders));
    }

}
