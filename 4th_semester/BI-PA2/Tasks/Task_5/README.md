# Task description
    The task is to implement classes that implement value added tax management.

    We assume that companies forward invoices to each other. The company that issues the invoice must deduct VAT from the invoiced amount to the state. Analogously, a company that receives (and pays) an invoice can claim a VAT refund from the state (under certain circumstances). The VAT refund is a weak spot that can be used for tax reduction and tax fraud. Therefore, the task is to implement the core of the system, which will make such tax cuts more difficult.

    Issued and received invoices are recorded by the CVATRegister class. Companies must register issued and received invoices. The register matches pairs of corresponding invoices and is able to find unpaired invoices. The invoice can be added to the register as well as canceled (e.g. in the case of incorrectly entered data). The class interface is as follows:

    implicit constructor
    initializes an empty registry instance,
    registerCompany ( name )
    the method introduces the entered company into the register. The given name is the official name of the company, this name will be used in exports from the register. The return value is a success (true)/failure (false) indicator. Consider it a failure if a company with the same name already exists in the register. The registry is quite tolerant when comparing business names:
    is not case sensitive when comparing,
    does not consider redundant spaces when comparing.
    These rules are used when setting up a new company and inserting/deleting invoices. For example, the names "My Company", "mY CoMpAnY", "My Company" and "mY CoMPAnY" are considered one company, but the names "My Company" and "MyCompany" refer to two different companies.
    addIssued ( invoice )
    method adds the invoice to the registry. This method is called by the company that issued the invoice. The return value is a success (true)/failure (false) flag. It is considered an error if the seller / buyer is not registered in the invoice, the seller and buyer are the same company or if the same invoice has already been entered using addIssued (the two invoices must differ in at least one of: seller/buyer/date/amount/VAT ).
    addAccepted ( invoice )
    the method adds the invoice to the register, this method is called by the company that accepted the invoice (buyer). Otherwise, the method behaves the same as addIssued.
    delIssued ( invoice )
    method removes the invoice from the register. This method is called by the company that issued the invoice and previously registered it. The return value is a success (true)/failure (false) flag. It is considered an error if the identical invoice was not previously registered using the addIssued method.
    delAccepted ( invoice )
    method removes the invoice from the register. This method is called by the company that accepted the invoice and previously registered it. The return value is a success (true)/failure (false) flag. It is considered an error if the identical invoice was not previously registered using the addAccepted method.
    unmatched ( company, sortOpt )
    the method finds all invoices that relate to the specified company and were not matched (that is, they were registered only with addIssued or only with addAccepted). The method returns a list of these invoices, the invoices will be sorted according to the criteria given by sortOpt. Invoices returned by this method will have the "official" name instead of the company name, i.e. the name that was entered when the company was registered using the registerCompany method. This official name will also be used for sorting.
    The CInvoice class represents a single invoice. The interface must comply with:

    constructor ( date, seller, buyer, amount, vat )
    initialization of the invoice with the date, name of the seller and buyer company, the invoiced amount and VAT.
    date, seller, buyer, amount, vat
    access methods for reading individual invoice components.
    next
    you can add additional public/non-public methods and member variables to the invoice interface that you will need for implementation.
    The CSortOpt class specifies the sorting criteria. All invoice folders can be used for sorting. For example, if we instantiate:

    CSortOpt () . addKey ( CSortOpt::BY_AMOUNT, true ) . addKey ( CSortOpt::BY_SELLER, false )
    then it is sorted according to the invoiced amount in ascending order (first sorting criterion) and for the same values of the invoiced amount, sorting according to the name of the seller is used in descending order (second sorting criterion). If the order is not clearly determined even in this way, the order of entering the invoice into the register will be used as a ranking criterion. The interface of the CSortOpt class is:
    implicit constructor
    initializes an empty instance of the class
    addKey ( sortBy, ascending )
    adds another sorting criterion sortBy, the sorting direction is given by the ascending flag (true = ascending, false = descending). You can sort by:
    BY_DATE - by invoice date,
    BY_SELLER - according to the official name of the selling company, sorted regardless of lowercase/uppercase letters,
    BY_BUYER - according to the official name of the buying company, sorted regardless of lowercase/uppercase letters,
    BY_AMOUNT - according to the invoiced amount,
    BY_VAT - according to VAT
    The CDate class implements a simple date, its implementation is ready in the test environment and you have it delivered for testing in the attached archive. Its implementation cannot be changed, the supplied implementation must remain in the conditional translation block.