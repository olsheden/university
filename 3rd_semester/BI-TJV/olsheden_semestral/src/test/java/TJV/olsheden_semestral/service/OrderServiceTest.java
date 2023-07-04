package TJV.olsheden_semestral.service;

import TJV.olsheden_semestral.Exception.FieldsCannotBeEmpty;
import TJV.olsheden_semestral.Exception.InvalidStateException;
import TJV.olsheden_semestral.Exception.NotFoundException;
import TJV.olsheden_semestral.domain.Order;
import TJV.olsheden_semestral.dtos.OrderDto;
import TJV.olsheden_semestral.repository.OrderReposiroty;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.testng.annotations.Test;

import java.time.LocalDateTime;
import java.util.*;
import java.util.function.Function;

import static org.mockito.Mockito.verify;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

@SpringBootTest
public class OrderServiceTest {

    protected Function<OrderDto, Order> orderConvertertoEntity;
    @Test
    public void testCreate() throws Exception {
        OrderReposiroty mockOrderRepository = mock(OrderReposiroty.class);

        Order expectedOrder = new Order();
        when(mockOrderRepository.save(expectedOrder)).thenReturn(expectedOrder);

        OrderService testClass = new OrderService(mockOrderRepository);

        Order actualOrder = testClass.create(expectedOrder);

        assertEquals(expectedOrder, actualOrder);

        verify(mockOrderRepository).save(expectedOrder);
    }

    @Test
    public void testCreateThrowsFieldsCannotBeEmpty() throws Exception {
        OrderReposiroty mockOrderRepository = mock(OrderReposiroty.class);

        OrderService testClass = new OrderService(mockOrderRepository);

        testClass.create(new Order());
    }

    @Test
    public void testCreateThrowsInvalidStateException() throws Exception {
        OrderReposiroty mockOrderRepository = mock(OrderReposiroty.class);

        when(mockOrderRepository.existsById(1L)).thenReturn(true);

        OrderService testClass = new OrderService(mockOrderRepository);
        List<String> productType = new ArrayList<>();
        productType.add("pizza");

        testClass.create( orderConvertertoEntity.apply(new OrderDto(1L, LocalDateTime.of(2022, 2, 13, 15, 56), 100L, productType, 12L, 1L, new ArrayList<Long>(1))));
    }

    @Test
    public void testReadAll() throws Exception {
        OrderReposiroty mockOrderRepository = mock(OrderReposiroty.class);

        Collection<Order> expectedOrders = Arrays.asList(new Order(), new Order(), new Order());
        when(mockOrderRepository.findAll()).thenReturn((List<Order>) expectedOrders);

        OrderService testClass = new OrderService(mockOrderRepository);

        Collection<Order> actualOrders = testClass.readAll();

        assertEquals(expectedOrders, actualOrders);

        verify(mockOrderRepository).findAll();
    }

    @Test
    public void testUpdate() throws Exception {
        OrderReposiroty mockOrderRepository = mock(OrderReposiroty.class);

        Order expectedOrder = new Order();
        when(mockOrderRepository.findById(1L)).thenReturn(Optional.of(expectedOrder));
        when(mockOrderRepository.save(expectedOrder)).thenReturn(expectedOrder);

        OrderService testClass = new OrderService(mockOrderRepository);

        Order actualOrder = testClass.update(expectedOrder);

        assertEquals(expectedOrder, actualOrder);

        verify(mockOrderRepository).findById(1L);
        verify(mockOrderRepository).save(expectedOrder);
    }

    @Test
    public void testUpdateThrowsNotFoundException() throws Exception {
        OrderReposiroty mockOrderRepository = mock(OrderReposiroty.class);

        when(mockOrderRepository.findById(1L)).thenReturn(Optional.empty());

        OrderService testClass = new OrderService(mockOrderRepository);
        List<String> productType = new ArrayList<>();
        productType.add("pizza");

        testClass.create( orderConvertertoEntity.apply(new OrderDto(1L, LocalDateTime.of(2022, 2, 13, 15, 56), 100L, productType, 12L, 1L, new ArrayList<Long>(1))));
    }

    @Test
    public void testDeleteById() throws Exception {
        OrderReposiroty mockOrderRepository = mock(OrderReposiroty.class);

        when(mockOrderRepository.findById(1L)).thenReturn(Optional.of(new Order()));

        OrderService testClass = new OrderService(mockOrderRepository);

        testClass.deleteById(1L);

        verify(mockOrderRepository).findById(1L);
        verify(mockOrderRepository).deleteById(1L);
    }

    @Test
    public void testDeleteByIdThrowsNotFoundException() throws Exception {
        OrderReposiroty mockOrderRepository = mock(OrderReposiroty.class);

        when(mockOrderRepository.findById(1L)).thenReturn(Optional.empty());

        OrderService testClass = new OrderService(mockOrderRepository);

        testClass.deleteById(1L);
    }


}
