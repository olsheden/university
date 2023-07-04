package TJV.olsheden_semestral.service;

import TJV.olsheden_semestral.Exception.FieldsCannotBeEmpty;
import TJV.olsheden_semestral.Exception.InvalidStateException;
import TJV.olsheden_semestral.Exception.NotFoundException;
import TJV.olsheden_semestral.domain.Client;
import TJV.olsheden_semestral.repository.ClientRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Collection;
import java.util.Optional;

@Service
public class ClientService {


    @Autowired
    protected ClientRepository clientRepository;

    public ClientService(ClientRepository clientRepository) {
        this.clientRepository = clientRepository;
    }

    public Client create(Client client) throws FieldsCannotBeEmpty, InvalidStateException {
        Long id = client.getId();
        if(client.getName() == null || client.getSurname() == null || client.getAge() == null)
            throw new FieldsCannotBeEmpty("You should fill all the client's fields");
        if(id != null && clientRepository.existsById(id))
            throw new InvalidStateException("Invalid state of order");
        return clientRepository.save(client);
    }

    public Optional<Client> readById(Long id) {
        return clientRepository.findById(id);
    }

    public Collection<Client> readAll() {
        return clientRepository.findAll();
    }

    public Client update(Client client) throws NotFoundException, FieldsCannotBeEmpty {
        if (clientRepository.findById(client.getId()).isEmpty())
            throw new NotFoundException("Client not found");

        if (client.getName() != null && client.getSurname() != null && client.getAge() != null){
            return clientRepository.save(client);
        }
        else{
            throw new FieldsCannotBeEmpty("You should fill all the client's fields");
        }
    }

    public void deleteById(Long id) throws NotFoundException {

        if (clientRepository.findById(id).isEmpty())
            throw new NotFoundException("Client not found");

        clientRepository.deleteById(id);

    }



}