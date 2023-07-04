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
import java.util.Set;
import java.util.function.Function;

@Component
public class ClientConverterToDto implements Function<Client, ClientDto> {

    @Autowired
    private final OrderService orderService;

    public ClientConverterToDto(OrderService orderService) {
        this.orderService = orderService;
    }

    @Override
    public ClientDto apply(Client client) {
        ClientDto clientDto = new ClientDto();
        clientDto.setId(client.getId());
        clientDto.setName(client.getName());
        clientDto.setSurname(client.getSurname());
        clientDto.setAge(client.getAge());
        Set<Long> ordersIds = new HashSet<>();
        for (Order order : client.getOrders()) {
            ordersIds.add(order.getId());
        }
        clientDto.setOrdersId(ordersIds);
        return clientDto;

    }
}
