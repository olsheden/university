package TJV.olsheden_semestral.service;

import static org.assertj.core.api.Assertions.assertThat;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

import java.util.*;

import TJV.olsheden_semestral.domain.Order;
import TJV.olsheden_semestral.repository.RestaurantRepository;
import org.junit.jupiter.api.Test;
import org.mockito.Mock;
import org.mockito.Mockito;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.mock.mockito.MockBean;

import static org.mockito.Mockito.verify;
import TJV.olsheden_semestral.Exception.FieldsCannotBeEmpty;
import TJV.olsheden_semestral.Exception.InvalidStateException;
import TJV.olsheden_semestral.Exception.NotFoundException;
import TJV.olsheden_semestral.domain.Client;
import TJV.olsheden_semestral.repository.ClientRepository;
import TJV.olsheden_semestral.service.ClientService;

@SpringBootTest
public class ClientServiceTest {


    @Autowired
    private ClientService clientService;

    @MockBean
    private ClientRepository clientRepository;

    @Test
    public void testCreate() throws Exception {
        ClientRepository mockClientRepository = mock(ClientRepository.class);

        Client expectedClient = new Client();
        when(mockClientRepository.save(expectedClient)).thenReturn(expectedClient);

        ClientService testClass = new ClientService(mockClientRepository);

        Client actualClient = testClass.create(expectedClient);

        assertEquals(expectedClient, actualClient);

        verify(mockClientRepository).save(expectedClient);
    }

    @Test
    public void testCreateThrowsFieldsCannotBeEmpty() throws Exception {
        ClientRepository mockClientRepository = mock(ClientRepository.class);

        ClientService testClass = new ClientService(mockClientRepository);

        testClass.create(new Client());
    }

    @Test
    public void testCreateThrowsInvalidStateException() throws Exception {
        ClientRepository mockClientRepository = mock(ClientRepository.class);

        when(mockClientRepository.existsById(1L)).thenReturn(true);

        ClientService testClass = new ClientService(mockClientRepository);

        testClass.create(new Client(1L, "John", "Doe", 25L, new HashSet<Order>()));
    }

    @Test
    public void testReadById() {
        ClientRepository mockClientRepository = mock(ClientRepository.class);

        Optional<Client> expectedClient = Optional.of(new Client());
        when(mockClientRepository.findById(1L)).thenReturn(expectedClient);

        ClientService testClass = new ClientService(mockClientRepository);

        Optional<Client> actualClient = testClass.readById(1L);

        assertEquals(expectedClient, actualClient);

        verify(mockClientRepository).findById(1L);
    }

    @Test
    public void testReadAll() {
        ClientRepository mockClientRepository = mock(ClientRepository.class);

        Collection<Client> expectedClients = Arrays.asList(new Client(), new Client(), new Client());
        when(mockClientRepository.findAll()).thenReturn((List<Client>) expectedClients);

        ClientService testClass = new ClientService(mockClientRepository);

        Collection<Client> actualClients = testClass.readAll();

        assertEquals(expectedClients, actualClients);

        verify(mockClientRepository).findAll();
    }

    @Test
    public void testUpdate() throws Exception {
        ClientRepository mockClientRepository = mock(ClientRepository.class);

        Client expectedClient = new Client();
        when(mockClientRepository.findById(1L)).thenReturn(Optional.of(expectedClient));
        when(mockClientRepository.save(expectedClient)).thenReturn(expectedClient);

        ClientService testClass = new ClientService(mockClientRepository);

        Client actualClient = testClass.update(expectedClient);

        assertEquals(expectedClient, actualClient);

        verify(mockClientRepository).findById(1L);
        verify(mockClientRepository).save(expectedClient);
    }

    @Test
    public void testUpdateThrowsNotFoundException() throws Exception {
        ClientRepository mockClientRepository = mock(ClientRepository.class);

        when(mockClientRepository.findById(1L)).thenReturn(Optional.empty());

        ClientService testClass = new ClientService(mockClientRepository);

        testClass.update(new Client(1L, "John", "Doe", 25L, new HashSet<Order>()) );
    }

    @Test
    public void testUpdateThrowsFieldsCannotBeEmpty() throws Exception {
        ClientRepository mockClientRepository = mock(ClientRepository.class);

        when(mockClientRepository.findById(1L)).thenReturn(Optional.of(new Client()));

        ClientService testClass = new ClientService(mockClientRepository);

        testClass.update(new Client());
    }

    @Test
    public void testDeleteById() throws Exception {
        ClientRepository mockClientRepository = mock(ClientRepository.class);

        when(    mockClientRepository.findById(1L)).thenReturn(Optional.of(new Client()));

        ClientService testClass = new ClientService(mockClientRepository);

        testClass.deleteById(1L);

        verify(mockClientRepository).findById(1L);
        verify(mockClientRepository).deleteById(1L);
    }

    @Test
    public void testDeleteByIdThrowsNotFoundException() throws Exception {
        ClientRepository mockClientRepository = mock(ClientRepository.class);

        when(mockClientRepository.findById(1L)).thenReturn(Optional.empty());

        ClientService testClass = new ClientService(mockClientRepository);

        testClass.deleteById(1L);
    }


}