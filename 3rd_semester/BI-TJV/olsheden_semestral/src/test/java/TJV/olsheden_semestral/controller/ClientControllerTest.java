package TJV.olsheden_semestral.controller;


import TJV.olsheden_semestral.Exception.FieldsCannotBeEmpty;
import TJV.olsheden_semestral.Exception.NotFoundException;
import TJV.olsheden_semestral.domain.Client;
import TJV.olsheden_semestral.dtos.ClientDto;
import TJV.olsheden_semestral.service.ClientService;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.*;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

import org.junit.Before;
import org.junit.jupiter.api.Test;
import org.junit.runner.RunWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.Mockito;
import org.mockito.junit.MockitoJUnitRunner;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.setup.MockMvcBuilders;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Optional;
import java.util.function.Function;

import static org.springframework.mock.http.server.reactive.MockServerHttpRequest.post;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.status;

@WebMvcTest(ClientController.class)
public class ClientControllerTest {

    private MockMvc mockMvc;

    @Mock
    private ClientService clientService;

    @Mock
    private Function<Client, ClientDto> clientConvertToDto;

    @Mock
    private Function<ClientDto, Client> clientConvertToEntity;

    @InjectMocks
    private ClientController clientController;

    @Before
    public void setUp() {
        mockMvc = MockMvcBuilders.standaloneSetup(clientController).build();
    }

    @Test
    public void testCreateClient() throws Exception {
        when(clientService.create(any(Client.class))).thenReturn(new Client());
        when(clientConvertToDto.apply(any(Client.class))).thenReturn(new ClientDto());

        mockMvc.perform(put("/clients/1")
                        .contentType(MediaType.APPLICATION_JSON)
                        .content("{\"field1\":\"value1\"}"))
                .andExpect(status().isOk());
    }


    @Test
    public void testReadOne() throws Exception {
        when(clientService.readById(1L)).thenReturn(Optional.of(new Client()));
        when(clientConvertToDto.apply(any(Client.class))).thenReturn(new ClientDto());

        mockMvc.perform(get("/clients/1"))
                .andExpect(status().isOk());
    }

    @Test
    public void testReadAll() throws Exception {
        when(clientService.readAll()).thenReturn(Arrays.asList(new Client()));
        when(clientConvertToDto.apply(any(Client.class))).thenReturn(new ClientDto());

        mockMvc.perform(get("/clients"))
                .andExpect(status().isOk());
    }

    @Test
    public void testUpdateClient() throws NotFoundException, FieldsCannotBeEmpty {
        ClientDto clientDto = new ClientDto(13L, "Denis", "Olshevskiy", 20L, new HashSet<>());
        Client client = new Client(13L, "Denis", "Olshevskiy", 20L);
        when(clientConvertToEntity.apply(clientDto)).thenReturn(client);

        clientController.updateClient(clientDto, 13L);

        verify(clientService).update(client);
    }

    @Test
    public void testDeleteClient() throws Exception {
        doNothing().when(clientService).deleteById(1L);

        mockMvc.perform(delete("/clients/1"))
                .andExpect(status().isOk());
    }
}
