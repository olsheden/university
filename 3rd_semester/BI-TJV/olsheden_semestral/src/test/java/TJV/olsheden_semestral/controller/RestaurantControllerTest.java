package TJV.olsheden_semestral.controller;


import TJV.olsheden_semestral.domain.Restaurant;
import TJV.olsheden_semestral.dtos.RestaurantDto;
import TJV.olsheden_semestral.service.RestaurantService;
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

@WebMvcTest(RestaurantControllerTest.class)
public class RestaurantControllerTest {
    private MockMvc mockMvc;

    @Mock
    private RestaurantService restaurantService;

    @Mock
    private Function<Restaurant, RestaurantDto> restaurantConvertToDto;

    @Mock
    private Function<RestaurantDto, Restaurant> restaurantConvertToEntity;

    @InjectMocks
    private RestaurantController restaurantController;

    @Before
    public void setUp() {
        mockMvc = MockMvcBuilders.standaloneSetup(restaurantController).build();
    }

    @Test
    public void testCreateRestaurant() throws Exception {
        when(restaurantService.create(any(Restaurant.class))).thenReturn(new Restaurant());
        when(restaurantConvertToDto.apply(any(Restaurant.class))).thenReturn(new RestaurantDto());

        mockMvc.perform(put("/restaurants/1")
                        .contentType(MediaType.APPLICATION_JSON)
                        .content("{\"field1\":\"value1\"}"))
                .andExpect(status().isOk());
    }

    @Test
    public void testReadOne() throws Exception {
        when(restaurantService.readById(1L)).thenReturn(Optional.of(new Restaurant()));
        when(restaurantConvertToDto.apply(any(Restaurant.class))).thenReturn(new RestaurantDto());

        mockMvc.perform(get("/restaurants/1"))
                .andExpect(status().isOk());
    }

    @Test
    public void testReadAll() throws Exception {
        when(restaurantService.readAll()).thenReturn(Arrays.asList(new Restaurant()));
        when(restaurantConvertToDto.apply(any(Restaurant.class))).thenReturn(new RestaurantDto());

        mockMvc.perform(get("/restaurants"))
                .andExpect(status().isOk());
    }

    @Test
    public void testUpdateRestaurant() throws Exception {
        doNothing().when(restaurantService).update(any(Restaurant.class));

        mockMvc.perform(put("/restaurants/1")
                        .contentType(MediaType.APPLICATION_JSON)
                        .content("{\"field1\":\"value1\"}"))
                .andExpect(status().isOk());

        mockMvc.perform(put("/restaurants/1")
                        .contentType(MediaType.APPLICATION_JSON)
                        .content("{\"field1\":\"value1\"}"))
                .andExpect(status().isOk());
    }

    @Test
    public void testDeleteRestaurant() throws Exception {
        doNothing().when(restaurantService).deleteById(1L);

        mockMvc.perform(delete("/restaurants/1"))
                .andExpect(status().isOk());
    }

}
