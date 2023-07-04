package TJV.olsheden_semestral.controller;

import TJV.olsheden_semestral.domain.Order;
import TJV.olsheden_semestral.dtos.OrderDto;
import TJV.olsheden_semestral.service.ClientService;
import TJV.olsheden_semestral.service.OrderService;
import org.junit.Before;
import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.setup.MockMvcBuilders;

import java.util.Arrays;
import java.util.Optional;
import java.util.function.Function;

import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.doNothing;
import static org.mockito.Mockito.when;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.status;

@WebMvcTest(OrderController.class)
public class OrderControllerTest {

    private MockMvc mockMvc;

    @Mock
    private OrderService orderService;

    @Mock
    private Function<Order, OrderDto> orderConvertToDto;

    @Mock
    private Function<OrderDto, Order> orderConvertToEntity;

    @InjectMocks
    private OrderController orderController;

    @Before
    public void setUp() {
        mockMvc = MockMvcBuilders.standaloneSetup(orderController).build();
    }

    @Test
    public void testCreateOrder() throws Exception {
        when(orderService.create(any(Order.class))).thenReturn(new Order());
        when(orderConvertToDto.apply(any(Order.class))).thenReturn(new OrderDto());

        mockMvc.perform(put("/orders/1")
                        .contentType(MediaType.APPLICATION_JSON)
                        .content("{\"field1\":\"value1\"}"))
                .andExpect(status().isOk());
    }

    @Test
    public void testReadOne() throws Exception {
        when(orderService.readById(1L)).thenReturn(Optional.of(new Order()));
        when(orderConvertToDto.apply(any(Order.class))).thenReturn(new OrderDto());

        mockMvc.perform(get("/orders/1"))
                .andExpect(status().isOk());
    }

    @Test
    public void testReadAll() throws Exception {
        when(orderService.readAll()).thenReturn(Arrays.asList(new Order()));
        when(orderConvertToDto.apply(any(Order.class))).thenReturn(new OrderDto());

        mockMvc.perform(get("/orders"))
                .andExpect(status().isOk());
    }

    @Test
    public void testUpdateOrder() throws Exception {
        doNothing().when(orderService).update(any(Order.class));

        mockMvc.perform(put("/orders/1")
                        .contentType(MediaType.APPLICATION_JSON)
                        .content("{\"field1\":\"value1\"}"))
                .andExpect(status().isOk());

        mockMvc.perform(put("/orders/1")
                        .contentType(MediaType.APPLICATION_JSON)
                        .content("{\"field1\":\"value1\"}"))
                .andExpect(status().isOk());
    }

    @Test
    public void testDeleteOrder() throws Exception {
        doNothing().when(orderService).deleteById(1L);

        mockMvc.perform(delete("/orders/1"))
                .andExpect(status().isOk());
    }

}
