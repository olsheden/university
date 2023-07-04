package TJV.olsheden_semestral.front.service;

import TJV.olsheden_semestral.front.client_api.ClientClient;
import TJV.olsheden_semestral.front.client_api.OrderClient;
import TJV.olsheden_semestral.front.domain.ClientDto;
import org.springframework.stereotype.Service;

import java.util.Collection;
import java.util.Optional;

@Service
public class ClientService {
    private ClientClient clientClient;

    public ClientService(ClientClient clientClient) {
        this.clientClient = clientClient;
    }

    public void create(ClientDto e) {
        clientClient.create(e);
    }

    public Collection<ClientDto> readAll() {
        return clientClient.readAll();
    }

    public Optional<ClientDto> readOne() {
        return clientClient.readOne();
    }

    public void setCurrentClient(long id) {
        clientClient.setCurrentClient(id);
    }


    public void update(ClientDto e) {
        clientClient.updateOne(e);
    }

    public void update(String name, String surname, Long age, Collection<Long> ordersId) {
        var cur = clientClient.readOne();
        if (cur.isPresent()) {
            var client = cur.get();
            client.name = name;
            client.age = age;
            client.surname = surname;
            client.ordersId = ordersId;
            update(client);
        }
    }


    public void deleteOne() {
        clientClient.deleteOne();
    }
}
